#include "cGraphicsManager.h"
#include "SDL2/cGraphicsSDL2.h"
#include "graphicsMain.h"
#include "cTextureManager.h"
#include "../../animations/cAnimationManager.h"
#include "../../animations/animationsMain.h"

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
#if STORM_ENABLE_DRAW_MANAGER != 0
    DrawAll();
#endif

    S_DrawText(m_DebugString, 5, 5);
    S_DrawText(S_GetTextureManager().GetDebugString(), 5, 25);

    m_Graphics->SwapBuffers();
    return true;
}
uint32_t cGraphicsManager::CreateObject(const std::string &filename, 
                                        uint32_t *id) {
    cTextureBase *txt = S_GetTextureManager().Load(filename, id);
    if (txt == nullptr) {
        // Error has occurred. Logging is handled by texture manager
        return 0;
    }
    return GenerateObject(txt);
}
void cGraphicsManager::DestroyObject(uint32_t &id) {
    auto iter = m_TextureObjects.find(id);
    if (iter == m_TextureObjects.end()) {
        return;
    }
    sGraphicsObject *obj = &iter->second;
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
    if (obj->m_IsAnimation) {
        S_GetAnimationManager().Unload(id);
    }
    obj = nullptr; //Not needed, but just in case leave it here
    m_TextureObjects.erase(iter);
}
sGraphicsObject *cGraphicsManager::GetObject(uint32_t &id) {
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
    txt->IncUsage();
    return GenerateObject(txt, &section);
}
void cGraphicsManager::TxtModVisible(uint32_t &id, bool &isVisible) {
    sGraphicsObject *tmp = GetObject(id);
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
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = point.x;
    tmp->m_DestRect.y = point.y;
}
void cGraphicsManager::TxtModPos(uint32_t &id, int &x, int &y) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = x;
    tmp->m_DestRect.y = y;
}
void cGraphicsManager::TxtModZ(uint32_t &id, int &z) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Z = z;
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sGraphicsObject::Cmp);
}
void cGraphicsManager::TxtModAngle(uint32_t &id, double &angle) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Angle = angle;
}
void cGraphicsManager::TxtModOpacity(uint32_t &id, uint8_t &opacity) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Opacity = opacity;
}
void cGraphicsManager::TxtModCenter(uint32_t &id, sPoint &center) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center = center;
}
void cGraphicsManager::TxtModCenter(uint32_t &id, int &x, int &y) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center.x = x;
    tmp->m_Center.y = y;
}
bool cGraphicsManager::IsOnScreen(sGraphicsObject *obj) {
    return obj->m_DestRect.x + obj->m_DestRect.w > 0 &&
           obj->m_DestRect.x < m_Graphics->GetWidth() &&
           obj->m_DestRect.y + obj->m_DestRect.h > 0 &&
           obj->m_DestRect.y < m_Graphics->GetHeight();
}
// Private methods
void cGraphicsManager::DrawAll() {
    for (auto i : m_OnScreen) {
        if (IsOnScreen(i)) {
            S_GetTextureManager().Draw(i);
        }
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
    sGraphicsObject tmp;
    tmp.m_Texture = texture;
    tmp.m_DestRect.w = texture->GetPxWidth();
    tmp.m_DestRect.h = texture->GetPxHeight();
    tmp.CalcMiddle();

    if (section != nullptr) {
        tmp.m_SrcRect = *section;
        tmp.m_IsSection = true;
    }
    
    m_TextureObjects[newId] = tmp;
    m_LastObject = &m_TextureObjects[newId];
    m_OnScreen.push_back(&m_TextureObjects[newId]);
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sGraphicsObject::Cmp);
    
    return newId;
}


} /* namespace StormFramework { */