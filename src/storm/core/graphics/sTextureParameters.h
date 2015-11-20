/* 
 * File:   sTextureParameters.h
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

struct sTextureParameters {
    double m_Angle;
    uint8_t m_Opacity;
    cTextureBase *m_Texture;
    sPoint m_Center;    // Center of texture
    sRect m_DestRect;   // Destination on screen
    bool m_IsVisible;
    sTextureParameters() : m_Angle(0), m_Opacity(255), 
                           m_Texture(nullptr), m_IsVisible(true) { }
    sTextureParameters(double angle, uint8_t opacity, cTextureBase *texture) : 
                       m_Angle(angle), m_Opacity(opacity), 
                       m_Texture(texture), m_IsVisible(true) { 
        CalcMiddle();
    }

    /* Calculate middle of texture, and set m_Center */
    void CalcMiddle() {
        if (m_Texture == nullptr) 
            return;
        m_Center.x = m_Texture->GetWidthPx() / 2;
        m_Center.y = m_Texture->GetHeightPx() / 2;
    }
};


} /* namespace StormFramework */
#endif  /* sTextureParameters_H__ */
