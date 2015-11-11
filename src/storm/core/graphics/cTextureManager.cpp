#include "cTextureManager.h"
#include "SDL2/cTextureSDL2.h"

namespace StormFramework {


cTextureManager::cTextureManager() : m_MemoryUsage(0) {
}
cTextureManager::~cTextureManager() {
    for (auto &i : m_Textures) {
        delete i.second;
    }
    m_Textures.clear();
    m_TextureFilenames.clear();
}

uint32_t cTextureManager::Load(const std::string &filename) {
    std::string fullPath = (char*)STORM_DIR_GRAPHICS + filename;
    cFileSystem::ConvertPath(fullPath);
    auto itt = m_TextureFilenames.find(fullPath);
    if (itt != m_TextureFilenames.end()) {
        // Texture with this filename is already loaded
        m_Textures[itt->second]->IncUsage();
        return itt->second;
    }
    
    cTextureBase *texture = CreateAndLoad(fullPath);
    if (texture == nullptr) {
        return 0;
    }
    
    uint32_t newId = 1;
    if (m_Textures.size() > 0) {
        auto iter = m_Textures.end();
        --iter;
        newId = iter->first + 1;
    }
    
    texture->SetUsage(1);
    m_Textures[newId] = texture;
    m_TextureFilenames[fullPath] = newId;
    m_MemoryUsage += (texture->GetMemoryUsage() / 1024);
    
    return newId;
}
int cTextureManager::Unload(uint32_t id) {
    auto iter = m_Textures.find(id);
    if (iter == m_Textures.end()) {
        return 0;
    }
    cTextureBase *tmp = iter->second;
    if (tmp->GetUsage() > 1) {
        delete tmp;
        m_Textures.erase(iter);
        m_MemoryUsage += (tmp->GetMemoryUsage() / 1024);
        return 1;
    } else {
        tmp->DecUsage();
        return -1;
    }
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr)
        return;
    
    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), x, y, 
              tmp->GetWidthPx(), tmp->GetHeightPx(), 0, 100);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, int &x, int &y) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr)
        return;

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, src.w, src.h, 0, 100);    
}
void cTextureManager::Draw(uint32_t &id, sRect &src, sRect &dest) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr)
        return;

    tmp->Draw(src.x, src.y, src.w, src.h, dest.x, dest.y, 
              dest.w, dest.h, 0, 100);
}
uint32_t cTextureManager::CreateSection(uint32_t textureId, sRect &section) {
    uint32_t newId = 1;
    if (m_Sections.size() > 0) {
         auto iter = m_Sections.end();
        --iter;
        newId = iter->first + 1;
    }
    sTextureSection tmp;
    tmp.m_TextureId = textureId;
    tmp.m_Section = section;
    m_Sections[newId] = tmp;
    return newId;
}
void cTextureManager::DrawSection(uint32_t &id, int &x, int &y) {
    auto iter = m_Sections.find(id);
    if (iter == m_Sections.end())
        return;

    Draw(iter->second.m_TextureId, iter->second.m_Section, x, y);
}
void cTextureManager::RemoveSection(uint32_t sectionId) {
    auto iter = m_Sections.find(sectionId);
    if (iter != m_Sections.end()) {
        m_Sections.erase(iter);
    }
}
cTextureBase *cTextureManager::GetTexture(uint32_t textureId) {
    if (m_Textures.find(textureId) == m_Textures.end()) {
        return nullptr;
    }
    return m_Textures[textureId];
}
cTextureBase *cTextureManager::CreateTextureObject() {
    switch (S_GetGraphicsApi()) {
        case STORM_API_SDL: break;
        case STORM_API_SDL2: return new cTextureSDL2();
        case STORM_API_GLES: break;
    }
    
    return nullptr;
}

cTextureBase *cTextureManager::CreateAndLoad(const std::string &filename) {
    cTextureBase *texture = CreateTextureObject();
    texture->SetFilename(filename);
    if (texture->Load() <= 0) {
        delete texture;
        return nullptr;
    }
    
    return texture;
}

} /* namespace StormFramework */