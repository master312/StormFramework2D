#include "cGraphicsSDL2.h"
#ifdef STORM_BUILD_SDL2

namespace StormFramework {


cGraphicsSDL2::cGraphicsSDL2() : m_Window(nullptr), m_Renderer(nullptr) {
}
cGraphicsSDL2::~cGraphicsSDL2() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

int cGraphicsSDL2::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        S_LogError("cGraphicsSDL2", "Could not initialize SDL2");
        return -1;
    }
    int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_Width, m_Height, flags);
    if (m_Window == nullptr) {
        S_LogError("cGraphicsSDL2", "Could not create window");
        return -1;
    }
    
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr) {
        S_LogError("cGraphicsSDL2", "Could not create SDL renderer");
        return -1;
    }
    
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    SDL_RendererInfo info;
    SDL_GetRendererInfo(m_Renderer, &info);
    m_MaxTextureW = info.max_texture_width;
    m_MaxTextureH = info.max_texture_height;
    
    S_LogInfo("cGraphicsSDL2", "SDL2 initialized");

    return 1;
}
void cGraphicsSDL2::SwapBuffers() {
    SDL_RenderPresent(m_Renderer);
}
void cGraphicsSDL2::ClearScreen() {
    SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 200);
    SDL_RenderClear(m_Renderer);
}

} /* namespace StormFramework */
#endif /* #ifdef STORM_BUILD_SDL2 */