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
void cGraphicsManager::DeInitialize() {
    S_GetTextureManager().UnloadAll();
    m_OnScreen.clear();
    m_GraphicsObjects.clear();
    m_LastObject = nullptr;
    delete m_Graphics;
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
    auto iter = m_GraphicsObjects.find(id);
    if (iter == m_GraphicsObjects.end()) {
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
    m_GraphicsObjects.erase(iter);
}
sGraphicsObject *cGraphicsManager::GetObject(uint32_t &id) {
    auto iter = m_GraphicsObjects.find(id);
    if (iter == m_GraphicsObjects.end()) {
        return nullptr;
    }
    return &m_GraphicsObjects[id];
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
uint32_t cGraphicsManager::CreateGeometry(sGeometry *geometry) {
    uint32_t objId = GenerateObject(nullptr, nullptr);
    m_LastObject->m_Geometry = geometry;
    return objId;
}
void cGraphicsManager::GraphModVisible(uint32_t &id, bool &isVisible) {
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
void cGraphicsManager::GraphModPos(uint32_t &id, sPoint &point) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = point.x;
    tmp->m_DestRect.y = point.y;
}
void cGraphicsManager::GraphModPos(uint32_t &id, int &x, int &y) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.x = x;
    tmp->m_DestRect.y = y;
}
void cGraphicsManager::GraphModZ(uint32_t &id, int &z) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Z = z;
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sGraphicsObject::Cmp);
}
void cGraphicsManager::GraphModAngle(uint32_t &id, double &angle) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Angle = angle;
}
void cGraphicsManager::GraphModOpacity(uint32_t &id, uint8_t &opacity) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Opacity = opacity;
}
void cGraphicsManager::GraphModCenter(uint32_t &id, sPoint &center) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center = center;
}
void cGraphicsManager::GraphModCenter(uint32_t &id, int &x, int &y) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_Center.x = x;
    tmp->m_Center.y = y;
}
void cGraphicsManager::GraphModSize(uint32_t &id, uint32_t &w, uint32_t &h) {
    sGraphicsObject *tmp = GetObject(id);
    if (tmp == nullptr) {
        return;
    }
    tmp->m_DestRect.w = w;
    tmp->m_DestRect.h = h;
}
bool cGraphicsManager::IsOnScreen(sGraphicsObject *obj) {
    return obj->m_DestRect.x + obj->m_DestRect.w > 0 &&
           obj->m_DestRect.x < m_Graphics->GetWidth() &&
           obj->m_DestRect.y + obj->m_DestRect.h > 0 &&
           obj->m_DestRect.y < m_Graphics->GetHeight();
}
// Private methods
int c = 0;
void cGraphicsManager::DrawAll() {
    c = 0;
    for (auto i : m_OnScreen) {
        c++;
        if (IsOnScreen(i)) {
            if (i->m_Texture != nullptr) {
                S_GetTextureManager().Draw(i);
            } else {
                DrawGeometry(i);
            }
        }
    }
}
void cGraphicsManager::DrawGeometry(sGraphicsObject *obj) {
    sGeometry *gg = obj->m_Geometry;
    if (gg == nullptr) {
        S_LogWarning("cGraphicsManager", 
                     "Tried to draw geometry without geometry... :D");
        return;
    }
    sRect &tmpDest = obj->m_DestRect;
    sColor *tmpColor = &obj->m_Geometry->m_Color;
    bool &tmpFill = obj->m_Geometry->m_IsFill;
    switch (gg->m_Type) {
        case RECTANGLE:{
            if (tmpFill) {
                m_Graphics->DrawFillRect(tmpDest, tmpColor);
            } else {
                m_Graphics->DrawRect(tmpDest, tmpColor);
            }
            break;
        }case CIRCLE: {
            uint32_t radius = ((sGeometryCircle*)obj->m_Geometry)->m_Radius;
            if (tmpFill) {
                m_Graphics->DrawFillCircle(tmpDest.x, tmpDest.x, radius);
            } else {
                m_Graphics->DrawCircle(tmpDest.x, tmpDest.x, radius);
            }
            break;
        }case TRIANGLE:{
            std::cout << "Draw Triangle " << std::endl;
            break;
        }
    }
}
uint32_t cGraphicsManager::GenerateObject(cTextureBase *texture,
                                          sRect *section /* = nullptr */) {
    uint32_t newId = 1;
    if (m_GraphicsObjects.size() > 0) {
        auto iter = m_GraphicsObjects.end();
        --iter;
        newId = iter->first + 1;
    }
    sGraphicsObject tmp;
    if (texture != nullptr) {   
        // This if condition is 'guard', in case of creating geometry object
        tmp.m_Texture = texture;
        if (section != nullptr) {
            tmp.m_SrcRect = *section;
            tmp.m_DestRect.w = tmp.m_SrcRect.w;
            tmp.m_DestRect.h = tmp.m_SrcRect.h;
            tmp.m_IsSection = true;
        } else {
            tmp.m_DestRect.w = texture->GetPxWidth();
            tmp.m_DestRect.h = texture->GetPxHeight();
        }
        tmp.CalcMiddle();
    } else {
        tmp.m_Texture = nullptr;
    }

    
    m_GraphicsObjects[newId] = tmp;
    m_LastObject = &m_GraphicsObjects[newId];
    m_OnScreen.push_back(&m_GraphicsObjects[newId]);
    std::sort(m_OnScreen.begin(), m_OnScreen.end(), sGraphicsObject::Cmp);
    
    return newId;
}


} /* namespace StormFramework { */