#include "cEventManager.h"
#include "SDL2/cEventSDL2.h"
#include "../layers/cLayerManager.h"
#include "../layers/layersMain.h"

namespace StormFramework {

cEventManager::cEventManager() {
    m_Input = nullptr;
}
cEventManager::cEventManager(int api) {
    m_Input = nullptr;
    SetApi(api);
}
cEventManager::~cEventManager() {
    if (m_Input != nullptr)
        delete m_Input;
}
void cEventManager::SetApi(int api) {
    switch (api) {
        case STORM_API_SDL:
            S_LogError("cEventManager", "Api 'SDL' not supported");
            return;
        case STORM_API_SDL2:
            m_Input = new cEventSDL2(); 
            break;
        case STORM_API_GLES:
            S_LogError("cEventManager", "Api 'GLES' not supported");
            return;
    }
}
void cEventManager::Tick() {
    m_Input->Update();
}
void cEventManager::CBOnKeyDown(StormKey key) {
    S_GetLayerManager().EventKeyDown(key);
}
void cEventManager::CBOnKeyUp(StormKey key) {
    S_GetLayerManager().EventKeyUp(key);
}
void cEventManager::CBOnTextType() {
    S_GetLayerManager().EventTextType();
}
void cEventManager::CBOnMouseDown(StormKey key) {
    S_GetLayerManager().EventMouseDown(key);
}
void cEventManager::CBOnMouseUp(StormKey key) {
    S_GetLayerManager().EventMouseUp(key);
}
void cEventManager::CBOnMouseScroll(int scroll) {
    S_GetLayerManager().EventMouseScroll(scroll);
}
void cEventManager::CBOnMouseMotion() {
     S_GetLayerManager().EventMouseMotion();
}
void cEventManager::CBOnWindowResize() {
    S_GetLayerManager().EventWindowResize();
}
void cEventManager::CBOnWindowStateChange(int state) {
    S_GetLayerManager().EventWindowStateChange(state);
}

} /* namespace StormFramework */