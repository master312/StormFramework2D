/* 
 * File:   cGraphicsSDL2.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:20 PM
 */

#ifndef CGRAPHICSSDL2_H__
#define CGRAPHICSSDL2_H__
#include "../cGraphicsBase.h"
#ifdef STORM_BUILD_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace StormFramework {

class cGraphicsSDL2 : public cGraphicsBase {
public:
    cGraphicsSDL2();
    ~cGraphicsSDL2();
    
    /* Initialize graphics api. Returns < 0 on error */
    int Initialize();
    
    void SwapBuffers();
    void ClearScreen();
    
    void DrawFillRect(sRect &rect, sColor *color = nullptr);
    void DrawRect(sRect &rect, sColor *color = nullptr);
    void DrawFillCircle(uint32_t &radius, sColor *color = nullptr);
    void DrawCircle(uint32_t &radius, sColor *color = nullptr);

    SDL_Renderer *GetRenderer() { return m_Renderer; }
private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;


    void SetDrawColor(sColor *color);
};

} /* namespace StormFramework */
#endif  /* STORM_BUILD_SDL2 */
#endif  /* CGRAPHICSSDL2_H__ */