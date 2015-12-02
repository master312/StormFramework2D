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
#include <cstring>
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
    /* Size of font */
    uint32_t m_Size;
    /* New line height */
    uint32_t m_LineHeight;
    /* Padding */
    /* 0-Up, 1-Right, 2-Down, 3-Left */
    uint32_t m_Padding[4];

    sBitmapFont() : m_TextureId(0), m_GraphicsId(0), 
                    m_Size(0), m_LineHeight(0) { 
        memset(m_Padding, 0, 4);
    }
    sBitmapFont(uint32_t texture, uint32_t graphics, 
                uint32_t size, uint32_t lineHeight) : 
                m_TextureId(texture), m_GraphicsId(graphics), 
                m_Size(size), m_LineHeight(lineHeight) { 
        memset(m_Padding, 0, 4);
    }
};


} /* namespace StormFramework */
#endif /* SBITMAPFONT_H__ */