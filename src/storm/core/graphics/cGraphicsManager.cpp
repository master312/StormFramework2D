#include "cGraphicsManager.h"
#include "SDL2/cGraphicsSDL2.h"

namespace StormFramework {

cGraphicsManager::cGraphicsManager() :
    m_Api(0),
    m_Graphics(nullptr),
    m_LastFrameTime(0),
    m_CurrentFps(0),
    m_FpsCountRefresh(0),
    m_TargetFps(0) {

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

    return 1;
}
bool cGraphicsManager::Tick() {
    m_Graphics->SwapBuffers();

    return true;
}




} /* namespace StormFramework { */