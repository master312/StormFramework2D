/* 
 * File:   sTextureObject.h
 * Author: master312
 *
 * Created on November 12, 2015, 9:04 PM
 */
 
#ifndef STEXTUREPARAMETERS_H__
#define STEXTUREPARAMETERS_H__
#include <iostream>
#include "../framework/frameworkMain.h"
#include "cTextureBase.h"

namespace StormFramework { 

struct sTextureObject {
    double m_Angle;
    uint8_t m_Opacity;
    cTextureBase *m_Texture;
    sPoint m_Center;    // Center of texture
    sRect m_DestRect;   // Destination on screen
    sRect m_SrcRect;    // Used only if object is texture section
    int32_t m_Z;        // Z coordinate
    bool m_IsVisible;
    bool m_IsSection;   // True if this object is texture section
    sTextureObject() : m_Angle(0), m_Opacity(255), 
                       m_Texture(nullptr), m_Z(0), m_IsVisible(true),
                       m_IsSection(false) { }
    sTextureObject(double angle, uint8_t opacity, cTextureBase *texture) : 
                       m_Angle(angle), m_Opacity(opacity), 
                       m_Texture(texture), m_Z(0), m_IsVisible(true),
                       m_IsSection(false) { 
        m_DestRect.w = m_Texture->GetWidthPx();
        m_DestRect.h = m_Texture->GetHeightPx();
        CalcMiddle();
    }

    /* Calculate middle of texture, and set m_Center */
    void CalcMiddle() {
        if (m_Texture == nullptr)
            return;
        m_Center.x = m_Texture->GetWidthPx() / 2;
        m_Center.y = m_Texture->GetHeightPx() / 2;
    }

    // Compare method. Used for sorting (std::sort)
    static bool Cmp(const sTextureObject *a,
                    const sTextureObject *b) {
        return a->m_Z < b->m_Z;
    }

};


} /* namespace StormFramework */
#endif  /* sTextureParameters_H__ */
