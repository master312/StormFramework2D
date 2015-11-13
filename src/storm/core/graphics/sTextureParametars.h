/* 
 * File:   sTextureParametars.h
 * Author: master312
 *
 * Created on November 12, 2015, 9:04 PM
 */
 
#ifndef STEXTUREPARAMETARS_H__
#define STEXTUREPARAMETARS_H__
#include <iostream>
#include "../framework/frameworkMain.h"

namespace StormFramework { 

struct sTextureParametars {
    double m_Angle;
    uint8_t m_Opacity;
    sTextureParametars() : m_Angle(0), m_Opacity(255) { }
    sTextureParametars(double angle, uint8_t opacity) : 
                       m_Angle(angle), m_Opacity(opacity) { }
};


} /* namespace StormFramework */
#endif  /* STEXTUREPARAMETARS_H__ */
