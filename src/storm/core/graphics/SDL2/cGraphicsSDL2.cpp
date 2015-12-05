#include "cGraphicsSDL2.h"
#ifdef STORM_BUILD_SDL2

namespace StormFramework {


cGraphicsSDL2::cGraphicsSDL2() : m_Window(nullptr), m_Renderer(nullptr) {
}
cGraphicsSDL2::~cGraphicsSDL2() {
    if (m_Renderer != nullptr && m_Window != nullptr) {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        m_Renderer = nullptr;
        m_Window = nullptr;
    }
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
    SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
    SDL_RenderClear(m_Renderer);
}

void cGraphicsSDL2::DrawFillRect(sRect &rect, sColor *color /*= nullptr*/) {
    SetDrawColor(color);
    SDL_RenderFillRect(m_Renderer, (SDL_Rect*)&rect);
}
void cGraphicsSDL2::DrawRect(sRect &rect, sColor *color /*= nullptr*/) {
    SetDrawColor(color);
    SDL_RenderDrawRect(m_Renderer, (SDL_Rect*)&rect);
}
void cGraphicsSDL2::DrawFillCircle(int &x, int &y, 
                                   uint32_t &radius, 
                                   sColor *color /*= nullptr*/) {
    SetDrawColor(color);
    int tmpX = 0;
    int tmpY = 0;
    for (int i = 0; i < 360; i++) {
        tmpX = x + (sin(i) * radius);
        tmpY = y + (cos(i) * radius);
        SDL_RenderDrawPoint(m_Renderer, tmpX, tmpY);
    }
}
void cGraphicsSDL2::DrawCircle(int &x, int &y, 
                               uint32_t &radius, 
                               uint32_t width /* = 1 */,
                               sColor *color /*= nullptr*/) {
    SetDrawColor(color);
    if (width == 0) {
        width = 1;
    }
    int tmpX = 0;
    int tmpY = 0;
    int tmpEndX = 0;
    int tmpEndY = 0;
    for (double i = 0.0; i < 360.0; i += 0.4) {
        tmpX = x + (cos(i) * radius);
        tmpY = y + (sin(i) * radius);
        if (width == 1) {
            SDL_RenderDrawPoint(m_Renderer, tmpX, tmpY);
        } else if (width > 1){
            tmpEndX = x + (cos(i) * (radius - width));
            tmpEndY = y + (sin(i) * (radius - width));
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX, tmpEndY);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX - 1, tmpEndY);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX, tmpEndY - 1);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX - 1, tmpEndY - 1);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX, tmpEndY + 1);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX + 1, tmpEndY);
            SDL_RenderDrawLine(m_Renderer, tmpX, tmpY, tmpEndX + 1, tmpEndY + 1);
        }
    }
}

// Private methods
void cGraphicsSDL2::SetDrawColor(sColor *color) {
    if (color != nullptr) {
        SDL_SetRenderDrawColor(m_Renderer, 
                               color->r, 
                               color->g, 
                               color->b, 255);
    } else {
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    }
}

} /* namespace StormFramework */
#endif /* #ifdef STORM_BUILD_SDL2 */