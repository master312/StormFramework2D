/* 
 * File:   cTextureSDL2.h
 * Author: master312
 *
 * Created on September 27, 2015, 3:23 AM
 */
#ifndef CTEXTURESDL2_H__
#define CTEXTURESDL2_H__
#include "../../../defines.h"
#ifdef STORM_BUILD_SDL2
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../cTextureBase.h"

namespace StormFramework {

class cGraphicsSDL2;
    
class cTextureSDL2 : public cTextureBase {
public:
    cTextureSDL2();
    ~cTextureSDL2();
    
    int Load(sColor *colorKey = nullptr);
    void Draw(const int &srcX, const int &srcY, 
              const int &srcW, const int &srcH,
              const int &destX, const int &destY, 
              const int &destW, const int &destH,
              const double &angle, const int &opacity, sPoint &center);
    
    uint32_t GetPxWidth() { return m_Width; }
    uint32_t GetPxHeight() { return m_Height; }

    void ModColor(uint8_t &r, uint8_t &g, uint8_t &b);
private:
    SDL_Texture *m_Texture;
    //True if texture was split into multiple chunks
    bool m_IsSplit;
    uint32_t m_Width, m_Height;
    cGraphicsSDL2 *p_Graphics;
    
    SDL_Texture *MakeTexture(SDL_Surface *sur, uint32_t &size);
protected:
    void Delete();
};


} /* namespace StormFramework */
#endif  /* CTEXTURESDL2_H */
#endif /* #ifdef STORM_BUILD_SDL2 */
