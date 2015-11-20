#include "cGraphicsManager.h"
#include "SDL2/cGraphicsSDL2.h"
#include "graphicsMain.h"
#include "cTextureManager.h"

namespace StormFramework {

cGraphicsManager::cGraphicsManager() :
    m_Api(0),
    m_Graphics(nullptr),
    m_CurrentFps(0),
    m_FpsCountRefresh(0) {
                                           
    std::stringstream ss;
    ss << "Storm Framework 2D ";
    ss << STORM_VERSION_MAJOR << ".";
    ss << STORM_VERSION_MINOR << ".";
    ss << STORM_VERSION_FIX;
    m_DebugVersion = ss.str();

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
    S_DrawText(m_DebugVersion, 5, 5);
    S_DrawText(S_GetTextureManager().GetDebugString(), 5, 25);
    S_GetTextureManager().DrawAll();
    m_Graphics->SwapBuffers();

    return true;
}




} /* namespace StormFramework { */