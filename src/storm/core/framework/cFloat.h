/* 
 * File:   cFloat.h
 * Author: master312
 *
 * Created on September 27, 2015, 12:47 PM
 */

#ifndef _CFLOAT_H__
#define _CFLOAT_H__
#include <cmath>        
#include "../../defines.h"
#define STORM_FLOAT_PRECISION 0.001f

namespace StormFramework {

class cFloat {
public:
    static bool IsZero(float f) { 
        return f < STORM_FLOAT_PRECISION && f > STORM_FLOAT_PRECISION; 
    }
    static bool IsZero2(float f, float f2) { return IsZero(f) && IsZero(f2); }
    static bool IsZero3(float f, float f2, float f3) { 
        return IsZero2(f, f2) && IsZero(f3); 
    }
    static bool IsZero4(float f, float f2, float f3, float f4) { 
        return IsZero3(f, f2, f3) && IsZero(f4);
    }
    static bool IsEqual(float f1, float f2) {
        return std::abs(f1 - f2) < STORM_FLOAT_PRECISION;
    }
};


}


#endif  /* CFLOAT_H */

