#include "cTextureManager.h"
#include "SDL2/cTextureSDL2.h"

namespace StormFramework {


cTextureManager::cTextureManager() : 
        m_MemoryUsage(0),
        m_UseColorKeying(true) {
    m_ColorKey.r = 255;
    m_ColorKey.g = 0;
    m_ColorKey.b = 255;
}
cTextureManager::~cTextureManager() {
    for (auto &i : m_Textures) {
        delete i.second;
    }
    m_Textures.clear();
    m_TextureFilenames.clear();
}
void cTextureManager::Initialize() {

}

cTextureBase *cTextureManager::Load(const std::string &filename, 
                                    uint32_t *id /* = nullptr */) {
    // TODO: This function can be written batter way
    std::string fullPath = (char*)STORM_DIR_GRAPHICS + filename;
    cFileSystem::ConvertPath(fullPath);
    auto itt = m_TextureFilenames.find(fullPath);
    if (itt != m_TextureFilenames.end()) { // This texture is already loaded
        m_Textures[itt->second]->IncUsage();
        UpdateDebugString();
        if (id != nullptr) {
            *id = itt->second;   
        }
        return m_Textures[itt->second];
    }
    
    cTextureBase *texture = CreateAndLoad(fullPath);
    if (texture == nullptr) {
        if (id != nullptr) {
            *id = 0;   
        }
        return nullptr;
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
    
    
    UpdateDebugString();

    if (id != nullptr) {
        *id = newId;   
    }

    return texture;
}
void cTextureManager::Unload(cTextureBase *texture) {

    m_MemoryUsage -= (texture->GetMemoryUsage() / 1024);
    uint32_t id = m_TextureFilenames[texture->GetFilename()];
    texture->Unload();
    m_TextureFilenames.erase(texture->GetFilename());
    m_Textures.erase(id);

    UpdateDebugString();
    delete texture;
}
void cTextureManager::Draw(sGraphicsObject *obj) {
    if (obj == nullptr) {
        return;
    }
    cTextureBase *tmp = obj->m_Texture;
    if (!obj->m_IsSection) {
        tmp->Draw(0, 0, tmp->GetPxWidth(), tmp->GetPxHeight(), 
                  obj->m_DestRect.x, obj->m_DestRect.y, 
                  obj->m_DestRect.w, obj->m_DestRect.h, 
                  obj->m_Angle, obj->m_Opacity, obj->m_Center);
    } else {
        tmp->Draw(obj->m_SrcRect.x, obj->m_SrcRect.y, 
                  obj->m_SrcRect.w, obj->m_SrcRect.h, 
                  obj->m_DestRect.x, obj->m_DestRect.y, 
                  obj->m_DestRect.w, obj->m_DestRect.h, 
                  obj->m_Angle, obj->m_Opacity, obj->m_Center);
    }
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr) {
        return;
    }
    
    tmp->Draw(0, 0, tmp->GetPxWidth(), tmp->GetPxHeight(), x, y, 
              tmp->GetPxWidth(), tmp->GetPxHeight(), 0, 255, m_DefCenter);
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y, int &w, int &h) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr) {
        return;
    }

    tmp->Draw(0, 0, tmp->GetPxWidth(), tmp->GetPxHeight(), x, y, 
              w, h, 0, 255, m_DefCenter);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, int &x, int &y) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr) {
        return;
    }

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, src.w, src.h, 
              0, 255, m_DefCenter);    
}
void cTextureManager::Draw(uint32_t &id, sRect &src, 
                           int &x, int &y, int &w, int &h) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr) {
        return;
    }

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, w, h, 
              0, 255, m_DefCenter);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, sRect &dest) {
    cTextureBase *tmp = m_Textures[id];
    if (tmp == nullptr) {
        return;
    }

    tmp->Draw(src.x, src.y, src.w, src.h, dest.x, dest.y, 
              dest.w, dest.h, 0, 255, m_DefCenter);
}
cTextureBase *cTextureManager::GetTexture(uint32_t &textureId) {
    if (m_Textures.find(textureId) == m_Textures.end()) {
        return nullptr;
    }
    return m_Textures[textureId];
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
    int status = 0;
    if (m_UseColorKeying) {
        status = texture->Load(&m_ColorKey);
    } else {
        status = texture->Load();
    }
    if (status <= 0) {
        delete texture;
        return nullptr;
    }

    return texture;
}
void cTextureManager::UpdateDebugString() {
    std::stringstream ss;
    ss << "Textures: " << m_Textures.size();
    ss << " Memory: " << GetMemoryUsage() << "kb";
    m_DebugString = ss.str();
}

} /* namespace StormFramework */
