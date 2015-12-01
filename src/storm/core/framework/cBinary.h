/* 
 * File:   cBinary.h
 * Author: master312
 *
 * Created on Thu March 5 10:50:50 2015
 * This class contains functions for converting various data types to binary (char array)
 * And binary data manipulation
 * TODO: Add Int64 methods
 */
#ifndef SCBINARY_H__
#define SCBINARY_H__
#include "../../defines.h"
#include <iostream>

namespace StormFramework {

class cBinary {
public:
    static bool IsBigEndian();
    
    static int32_t ByteToInt32(char *buffer, int offset);
    static uint32_t ByteToUint32(char *buffer, int offset);
    static int16_t ByteToInt16(char *buffer, int offset);
    static uint16_t ByteToUint16(char *buffer, int offset);
    static float ByteToFloat(char *buffer, int offset);
    
    static void Int32ToByte(int32_t &_int, char *dest);
    static void Uint32ToByte(uint32_t &_int, char *dest);
    static void Int16ToByte(int16_t &_short, char *dest);
    static void Uint16ToByte(uint16_t &_short, char *dest);
    static void FloatToByte(float &_float, char *dest);
    
    static void ByteCopy(char *src, char *dest, int destOffset, int srcLen);
};

} /* namespace StormFramework */
#endif /* STORM_CDATA_H__ */