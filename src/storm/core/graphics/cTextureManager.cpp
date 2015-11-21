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
        m_OnScreen.push_back(&m_TextureParameters[id]);
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
    m_OnScreen.push_back(&m_TextureParameters[id]);
    UpdateDebugString();
    return id;
}
int cTextureManager::Unload(uint32_t id) {
    auto iter = m_TextureParameters.find(id);
    if (iter == m_TextureParameters.end()) {
        return 0;
    }
    sTextureParameters *tmpPar = &iter->second;
    cTextureBase *tmp = tmpPar->m_Texture;

    if (tmpPar->m_IsVisible) {
        // If texture is visible, remove if form 'OnScreen' vector
        for (uint32_t i = 0; i < m_OnScreen.size(); i++) {
            if (m_OnScreen[i] == tmpPar) {
                m_OnScreen.erase(m_OnScreen.begin() + i);
                break;
            }
        }
    }
    tmpPar = nullptr;   // This is not required, but just live it here :) 

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
void cTextureManager::DrawAll() {
    for (auto i : m_OnScreen) {
        Draw(i);
    }
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y) {
    sTextureParameters *tmpP = GetTexturePar(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;
    
    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), x, y, 
              tmp->GetWidthPx(), tmp->GetHeightPx(), 
              tmpP->m_Angle, tmpP->m_Opacity, tmpP->m_Center);
}
void cTextureManager::Draw(uint32_t &id, int &x, int &y, int &w, int &h) {
    sTextureParameters *tmpP = GetTexturePar(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), x, y, 
              w, h, tmpP->m_Angle, tmpP->m_Opacity, tmpP->m_Center);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, int &x, int &y) {
    sTextureParameters *tmpP = GetTexturePar(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, src.w, src.h, 
              tmpP->m_Angle, tmpP->m_Opacity, tmpP->m_Center);    
}
void cTextureManager::Draw(uint32_t &id, sRect &src, 
                           int &x, int &y, int &w, int &h) {
    sTextureParameters *tmpP = GetTexturePar(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, x, y, w, h, 
              tmpP->m_Angle, tmpP->m_Opacity, tmpP->m_Center);
}
void cTextureManager::Draw(uint32_t &id, sRect &src, sRect &dest) {
    sTextureParameters *tmpP = GetTexturePar(id);
    if (tmpP == nullptr) {
        return;
    }
    cTextureBase *tmp = tmpP->m_Texture;

    tmp->Draw(src.x, src.y, src.w, src.h, dest.x, dest.y, 
              dest.w, dest.h, tmpP->m_Angle, 
              tmpP->m_Opacity, tmpP->m_Center);
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
void cTextureManager::ModVisible(uint32_t &id, bool &isVisible) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    if (tmp->m_IsVisible && !isVisible) {
        // Changed from visible to non-visible
        for (uint32_t i = 0; i < m_OnScreen.size(); i++) {
            if (m_OnScreen[i] == tmp) {
                m_OnScreen.erase(m_OnScreen.begin() + i);
                break;
            }
        }
    } else if (!tmp->m_IsVisible && isVisible) {
        // Changed from non-visible to visible
        m_OnScreen.push_back(tmp);
    }
    tmp->m_IsVisible = isVisible;    
}
void cTextureManager::ModPos(uint32_t &id, sPoint &point) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = point.x;
    tmp->m_DestRect.y = point.y;
}
void cTextureManager::ModPos(uint32_t &id, int &x, int &y) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = x;
    tmp->m_DestRect.y = y;
}


void cTextureManager::ModZ(uint32_t &id, int &z) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Z = z;
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sTextureParameters::Cmp);
}
void cTextureManager::ModAngle(uint32_t &id, double &angle) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Angle = angle;
}
void cTextureManager::ModOpacity(uint32_t &id, uint8_t &opacity) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Opacity = opacity;
}
void cTextureManager::ModCenter(uint32_t &id, sPoint &center) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center = center;
}
void cTextureManager::ModCenter(uint32_t &id, int &x, int &y) {
    sTextureParameters *tmp = GetTexturePar(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center.x = x;
    tmp->m_Center.y = y;
}
cTextureBase *cTextureManager::GetTexture(uint32_t &textureId) {
    if (m_Textures.find(textureId) == m_Textures.end()) {
        return nullptr;
    }
    return m_Textures[textureId];
}
sTextureParameters *cTextureManager::GetTexturePar(uint32_t &textureId) {
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
    tmp.CalcMiddle();
    m_TextureParameters[newId] = tmp;
    return newId;
}
void cTextureManager::Draw(sTextureParameters *par) {
    if (par == nullptr || !par->m_IsVisible) {
        return;
    }
    cTextureBase *tmp = par->m_Texture;
    tmp->Draw(0, 0, tmp->GetWidthPx(), tmp->GetHeightPx(), 
              par->m_DestRect.x, par->m_DestRect.y, 
              tmp->GetWidthPx(), tmp->GetHeightPx(), 
              par->m_Angle, par->m_Opacity, par->m_Center);
}
void cTextureManager::UpdateDebugString() {
    std::stringstream ss;
    ss << "Textures: " << m_Textures.size();
    ss << " Instances: " << m_TextureParameters.size();
    m_DebugString = ss.str();
}

} /* namespace StormFramework */
