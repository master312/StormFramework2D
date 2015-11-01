/* 
 * File:   eventsMain.h
 * Author: master312
 *
 * Created on Thu March 5 10:50:50 2015
 * This class contains functions for converting various data types to binary (char array)
 * And binary data manipulation
 */
#ifndef STORM_CDATA_H__
#define STORM_CDATA_H__
#include "../../defines.h"
#include <cstring>
#include <iostream>

namespace StormFramework {

class cData {
public:
    static bool IsBigEndian();
    
    static int ByteToInt(char *buffer, int offset);
    static float ByteToFloat(char *buffer, int offset);
    static short ByteToShort(char *buffer, int offset);
    
    static void IntToByte(int &_int, char *dest);
    static void FloatToByte(float &_float, char *dest);
    static void ShortToByte(short &_short, char *dest);
    
    static void ByteCopy(char *src, char *dest, int destOffset, int srcLen);
};

} /* namespace StormFramework */
#endif /* STORM_CDATA_H__ */