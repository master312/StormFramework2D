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
    sTextureParameters() : m_Angle(0), m_Opacity(255), m_Texture(nullptr) { }
    sTextureParameters(double angle, uint8_t opacity, cTextureBase *texture) : 
                       m_Angle(angle), m_Opacity(opacity), 
                       m_Texture(texture) { }
};


} /* namespace StormFramework */
#endif  /* sTextureParameters_H__ */
