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

namespace StormFramework {

class cGraphicsSDL2 : public cGraphicsBase {
public:
    cGraphicsSDL2();
    ~cGraphicsSDL2();
    
    /* Initialize graphics api. Returns < 0 on error */
    int Initialize();
    
    void SwapBuffers();
    void ClearScreen();
    
    SDL_Renderer *GetRenderer() { return m_Renderer; }
private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};

} /* namespace StormFramework */
#endif  /* STORM_BUILD_SDL2 */
#endif  /* CGRAPHICSSDL2_H__ */