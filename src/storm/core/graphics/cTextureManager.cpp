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
    // TODO: This function can be written batter way
    std::string fullPath = (char*)STORM_DIR_GRAPHICS + filename;
    cFileSystem::ConvertPath(fullPath);
    auto itt = m_TextureFilenames.find(fullPath);
    if (itt != m_TextureFilenames.end()) { // This texture is already loaded
        m_Textures[itt->second]->IncUsage();
        uint32_t id = CreateParameters(m_Textures[itt->second]);
        UpdateDebugString();
        return id;
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
    
    uint32_t id = CreateParameters(m_Textures[newId]);
    UpdateDebugString();
    return id;
}
int cTextureManager::Unload(uint32_t id) {
    auto iter = m_TextureParameters.find(id);
    if (iter == m_TextureParameters.end()) {
        return 0;
    }
    
    cTextureBase *tmp = iter->second.m_Texture;
    
    m_TextureParameters.erase(iter);
    
    int toReturn;
    if (tmp->GetUsage() <= 1) {
        // This texture is not in use anymore
        auto txtIter = m_TextureFilenames.find(tmp->GetFilename());
        if (txtIter == m_TextureFilenames.end()) {
            S_LogError("cTextureManager", "Fatal on texture unload");
            return -1;
        }

        m_Textures.erase(txtIter->second);
        m_TextureFilenames.erase(txtIter);
        m_MemoryUsage -= (tmp->GetMemoryUsage() / 1024);
        delete tmp;
        toReturn = 0;
    } else {
        // Other objects are still using this texture
        tmp->DecUsage();
        toReturn = -1;
    }
    UpdateDebugString();

    return toReturn;
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y) {
    sTextureParameters *tmpP = GetTextureParametars(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;
    
    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), x, y, 
              tmp->GetWidthPx(), tmp->GetHeightPx(), 
              tmpP->m_Angle, tmpP->m_Opacity);
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y, int &w, int &h) {
    sTextureParameters *tmpP = GetTextureParametars(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), x, y, 
              w, h, tmpP->m_Angle, tmpP->m_Opacity);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, int &x, int &y) {
    sTextureParameters *tmpP = GetTextureParametars(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, src.w, src.h, 
              tmpP->m_Angle, tmpP->m_Opacity);    
}
void cTextureManager::Draw(uint32_t &id, sRect &src, 
                           int &x, int &y, int &w, int &h) {
    sTextureParameters *tmpP = GetTextureParametars(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, w, h, 
              tmpP->m_Angle, tmpP->m_Opacity);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, sRect &dest) {
    sTextureParameters *tmpP = GetTextureParametars(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, dest.x, dest.y, 
              dest.w, dest.h, tmpP->m_Angle, tmpP->m_Opacity);
}
uint32_t cTextureManager::CreateSection(uint32_t &textureId, sRect &section) {
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
    if (iter == m_Sections.end()) {
        return;
    }

    Draw(iter->second.m_TextureId, iter->second.m_Section, x, y);
}
void cTextureManager::DrawSection(uint32_t &id, int &x, int &y, 
                                  int &w, int &h) {
    auto iter = m_Sections.find(id);
    if (iter == m_Sections.end()) {
        return;
    }

    Draw(iter->second.m_TextureId, iter->second.m_Section, 
         x, y, w, h);
}
void cTextureManager::RemoveSection(uint32_t sectionId) {
    auto iter = m_Sections.find(sectionId);
    if (iter != m_Sections.end()) {
        m_Sections.erase(iter);
    }
}
void cTextureManager::ModAngle(uint32_t &id, double &angle) {
    sTextureParameters *tmp = GetTextureParametars(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Angle = angle;
}
void cTextureManager::ModOpacity(uint32_t &id, uint8_t &opacity) {
    sTextureParameters *tmp = GetTextureParametars(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Opacity = opacity;
}
cTextureBase *cTextureManager::GetTexture(uint32_t &textureId) {
    if (m_Textures.find(textureId) == m_Textures.end()) {
        return nullptr;
    }
    return m_Textures[textureId];
}
sTextureParameters *cTextureManager::GetTextureParametars(uint32_t &textureId) {
    auto iter = m_TextureParameters.find(textureId);
    if (iter == m_TextureParameters.end()) {
        return nullptr;
    }
    return &m_TextureParameters[textureId];
}
// Private methods
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
    if (texture == nullptr) {
        S_LogError("cTextureBase", "Api not supported");
        return nullptr;
    }
    texture->SetFilename(filename);
    if (texture->Load() <= 0) {
        delete texture;
        return nullptr;
    }

    return texture;
}

uint32_t cTextureManager::CreateParameters(cTextureBase *texture) {
    uint32_t newId = 1;
    if (m_TextureParameters.size() > 0) {
        auto iter = m_TextureParameters.end();
        --iter;
        newId = iter->first + 1;
    }
    sTextureParameters tmp;
    tmp.m_Texture = texture;
    m_TextureParameters[newId] = tmp;
    return newId;
}

void cTextureManager::UpdateDebugString() {
    std::stringstream ss;
    ss << "Textures: " << m_Textures.size();
    ss << " Instances: " << m_TextureParameters.size();
    m_DebugString = ss.str();
}

} /* namespace StormFramework */
