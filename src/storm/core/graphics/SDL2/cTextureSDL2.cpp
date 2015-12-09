#include "../../../defines.h"
#ifdef STORM_BUILD_SDL2
#include "cTextureSDL2.h"
#include "cGraphicsSDL2.h"
#include "../graphicsMain.h"
#include "../cGraphicsManager.h"

namespace StormFramework {

    
cTextureSDL2::cTextureSDL2() : m_Texture(nullptr), m_IsSplit(false), 
                               m_Width(0), m_Height(0) {
    cGraphicsManager *gm = &S_GetGraphicsManager();
    p_Graphics = (cGraphicsSDL2*)gm->GetGraphics();
    if (p_Graphics == nullptr) {
        S_LogError("cTextureSDL2", "Graphics not initialized!");
        return;
    }
}
cTextureSDL2::~cTextureSDL2() {
}
int cTextureSDL2::Load(sColor *colorKey /*= nullptr*/) {
    SDL_Surface *tmpSur = IMG_Load(m_Filename.c_str());
    if (tmpSur == nullptr) {
        S_LogError("cTextureSDL2", 
                   "Texture '%s' not found", m_Filename.c_str());
        return -1;
    }
    
    // TODO: Split texture if it is bigger resolution that hardware supports
    m_Width = tmpSur->w;
    m_Height = tmpSur->h;
    
    uint32_t maxW = p_Graphics->GetMaxTxtWidth();
    uint32_t maxH = p_Graphics->GetMaxTxtHeight();
    if (m_Width > maxW || m_Height > maxH) {
        S_LogError("cTextureSDL2", 
                   "Texture '%s' is bigger then hardware supports");
        return -2;
    }
    
    if (colorKey != nullptr) {
        // Sets texture color key, if keying is enabled
        uint32_t tmpKey = SDL_MapRGB(tmpSur->format, 
                                     colorKey->r, 
                                     colorKey->g, 
                                     colorKey->b); 
        SDL_SetColorKey(tmpSur, SDL_TRUE, tmpKey);
    }

    m_Texture = MakeTexture(tmpSur, m_MemoryUsage);
    
    SDL_FreeSurface(tmpSur);
    
    if (m_Texture == nullptr) {
        return -3;
    }
    
    S_LogDebug("cTextureSDL2", "Texture '%s' loaded", m_Filename.c_str());
    
    return 1;
}
void cTextureSDL2::Draw(const int &srcX, const int &srcY, 
    const int &srcW, const int &srcH, const int &destX, const int &destY, 
    const int &destW, const int &destH, const double &angle, const int &opacity,
    sPoint &center) {
    
    //TODO: OPtimizeShitHere!
    SDL_Rect srcRect = {srcX, srcY, srcW, srcH};
    SDL_Rect destRect = {destX - center.x, destY - center.y, destW, destH};

    SDL_Texture *tmpTx = m_Texture;
    SDL_Renderer *gRenderer = p_Graphics->GetRenderer();
    
    if (opacity != 255) {
        SDL_SetTextureAlphaMod(tmpTx, opacity);
    }
    if (angle != 0) {
        SDL_RenderCopyEx(gRenderer, tmpTx, &srcRect, 
                         &destRect, angle, (SDL_Point*)&center, 
                         SDL_FLIP_NONE);
    } else {
        SDL_RenderCopy(gRenderer, tmpTx, &srcRect, &destRect);
    }
    if (opacity != 255) {
        SDL_SetTextureAlphaMod(tmpTx, 255);
    }
}
void cTextureSDL2::ModColor(uint8_t &r, uint8_t &g, uint8_t &b) {
    SDL_SetTextureColorMod(m_Texture, r, g, b);
}
// Private methods
SDL_Texture *cTextureSDL2::MakeTexture(SDL_Surface *sur, uint32_t &size) {
    SDL_Renderer *renderer = p_Graphics->GetRenderer();
    SDL_Texture *tmp = SDL_CreateTextureFromSurface(renderer, sur);
    if (tmp == nullptr) {
        S_LogError("cTextureManagerSDL2", "Could not create SDL_Texture!");
        return nullptr;
    }
    size = sur->w * sur->h * sur->format->BytesPerPixel;
    SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
    return tmp;
}
// Protected methods
void cTextureSDL2::Delete() {
    if (m_Texture == nullptr)
        return;
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
    S_LogDebug("cTextureSDL2", 
               "Texture '%s' unloaded from memory", m_Filename.c_str());
}

} /* namespace StormFramework */
#endif /* #ifdef STORM_BUILD_SDL2 */
