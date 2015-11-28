#include "cGraphicsManager.h"
#include "SDL2/cGraphicsSDL2.h"
#include "graphicsMain.h"
#include "cTextureManager.h"

namespace StormFramework {

cGraphicsManager::cGraphicsManager() :
        m_Api(0),
        m_Graphics(nullptr),
        m_LastObject(nullptr) {
                                           
    std::stringstream ss;
    ss << "Storm Framework 2D ";
    ss << STORM_VERSION_MAJOR << ".";
    ss << STORM_VERSION_MINOR << ".";
    ss << STORM_VERSION_FIX;
    m_DebugString = ss.str();

}
cGraphicsManager::~cGraphicsManager() {
    delete m_Graphics;
}

int cGraphicsManager::Initialize() {
    switch (S_GetGraphicsApi()) {
        case STORM_API_SDL:
            S_LogError("cGraphicsManager", "Api 'SDL' not supported");
            break;
        case STORM_API_SDL2:
            m_Graphics = new cGraphicsSDL2(); 
            break;
        case STORM_API_GLES:
            S_LogError("cGraphicsManager", "Api 'GLES' not supported");
            break;
    }

    m_Graphics->Initialize();
    m_Graphics->ClearScreen();

    S_LoadFont("default.xml");

    return 1;
}
bool cGraphicsManager::Tick() {    
    DrawAll();

    S_DrawText(m_DebugString, 5, 5);
    S_DrawText(S_GetTextureManager().GetDebugString(), 5, 25);

    m_Graphics->SwapBuffers();
    return true;
}
uint32_t cGraphicsManager::LoadTexture(const std::string &filename, 
                                       uint32_t *id) {
    cTextureBase *txt = S_GetTextureManager().Load(filename, id);
    if (txt == nullptr) {
        // Error has occurred. Logging is handled by texture manager
        return 0;
    }
    return GenerateObject(txt);
}
void cGraphicsManager::UnloadTexture(uint32_t &id) {
    auto iter = m_TextureObjects.find(id);
    if (iter == m_TextureObjects.end()) {
        return;
    }
    sTextureObject *obj = &iter->second;
    obj->m_Texture->DecUsage();
    if (m_LastObject == obj) {
        m_LastObject = nullptr;
    }
    if (obj->m_IsVisible) {
        for (uint32_t i = 0; i < m_OnScreen.size(); i++) {
            if (m_OnScreen[i] == obj) {
                m_OnScreen.erase(m_OnScreen.begin() + i);
                break;
            }
        }
    }
    obj = nullptr; //Not needed, but just in case leave it here
    m_TextureObjects.erase(iter);
}
sTextureObject *cGraphicsManager::GetObject(uint32_t &id) {
    auto iter = m_TextureObjects.find(id);
    if (iter == m_TextureObjects.end()) {
        return nullptr;
    }
    return &m_TextureObjects[id];
}
uint32_t cGraphicsManager::CreateSection(const std::string &filename, 
                                         sRect &section) {
    cTextureBase *txt = S_GetTextureManager().Load(filename);
    if (txt == nullptr) {
        // Error has occurred. Logging is handled by texture manager
        return 0;
    }
    return GenerateObject(txt, &section);
}
uint32_t cGraphicsManager::CreateSection(uint32_t &id, sRect &section) {
    cTextureBase *txt = S_GetTextureManager().GetTexture(id);
    if (txt == nullptr) {
        return 0;
    }
    return GenerateObject(txt, &section);
}
void cGraphicsManager::TxtModVisible(uint32_t &id, bool &isVisible) {
    sTextureObject *tmp = GetObject(id);
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
void cGraphicsManager::TxtModPos(uint32_t &id, sPoint &point) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = point.x;
    tmp->m_DestRect.y = point.y;
}
void cGraphicsManager::TxtModPos(uint32_t &id, int &x, int &y) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = x;
    tmp->m_DestRect.y = y;
}
void cGraphicsManager::TxtModZ(uint32_t &id, int &z) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Z = z;
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sTextureObject::Cmp);
}
void cGraphicsManager::TxtModAngle(uint32_t &id, double &angle) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Angle = angle;
}
void cGraphicsManager::TxtModOpacity(uint32_t &id, uint8_t &opacity) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Opacity = opacity;
}
void cGraphicsManager::TxtModCenter(uint32_t &id, sPoint &center) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center = center;
}
void cGraphicsManager::TxtModCenter(uint32_t &id, int &x, int &y) {
    sTextureObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center.x = x;
    tmp->m_Center.y = y;
}
// Private methods
void cGraphicsManager::DrawAll() {
    for (auto i : m_OnScreen) {
        S_GetTextureManager().Draw(i);
    }
}
uint32_t cGraphicsManager::GenerateObject(cTextureBase *texture,
                                          sRect *section /* = nullptr */) {
    uint32_t newId = 1;
    if (m_TextureObjects.size() > 0) {
        auto iter = m_TextureObjects.end();
        --iter;
        newId = iter->first + 1;
    }
    sTextureObject tmp;
    tmp.m_Texture = texture;
    tmp.m_DestRect.w = texture->GetWidthPx();
    tmp.m_DestRect.h = texture->GetHeightPx();
    tmp.CalcMiddle();
    m_TextureObjects[newId] = tmp;

    if (section != nullptr) {
        tmp.m_SrcRect = *section;
        tmp.m_IsSection = true;
    }

    m_LastObject = &m_TextureObjects[newId];
    m_OnScreen.push_back(&m_TextureObjects[newId]);
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sTextureObject::Cmp);
    
    return newId;
}


} /* namespace StormFramework { */