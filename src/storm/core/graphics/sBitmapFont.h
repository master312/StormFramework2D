/* 
 * File:   sBitmapFont.h
 * Author: master312
 *
 * Created on November 11, 2015, 4:34 PM
 */

#ifndef SBITMAPFONT_H__
#define SBITMAPFONT_H__
#include <iostream>
#include <map>
#include "../framework/frameworkMain.h"

namespace StormFramework {

struct sBitmapChar {
    sRect srcRect;
    uint32_t xOffset;
    uint32_t yOffset;
    uint32_t advance;
};

struct sBitmapFont {
    std::map<char, sBitmapChar> m_Characters;
    /* ID of raw texture */
    uint32_t m_TextureId;
    /* ID of graphics object */
    uint32_t m_GraphicsId;
    sBitmapFont() { }
    sBitmapFont(uint32_t texture, uint32_t graphics) : 
                m_TextureId(texture), m_GraphicsId(graphics) { }
};


} /* namespace StormFramework */
#endif /* SBITMAPFONT_H__ */