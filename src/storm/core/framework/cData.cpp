#include <cstring>
#include "cData.h"

namespace StormFramework {

bool cData::IsBigEndian() {
    int a = 1;
    return !((char*) &a)[0];    
}
int32_t cData::ByteToInt32(char *buffer, int offset) {
    int32_t a = 0;
    if (IsBigEndian()) {
        for (int i = 0; i < 4; i++)
            ((char*) &a)[i] = buffer[i + offset];
    } else {
        for(int i = 0; i < 4; i++)
            ((char*) &a)[3 - i] = buffer[i + offset];
    }
    return a;
}
uint32_t cData::ByteToUint32(char *buffer, int offset) {
    uint32_t a = 0;
    if (IsBigEndian()) {
        for (int i = 0; i < 4; i++)
            ((char*) &a)[i] = buffer[i + offset];
    } else {
        for(int i = 0; i < 4; i++)
            ((char*) &a)[3 - i] = buffer[i + offset];
    }
    return a;
}
int16_t cData::ByteToInt16(char *buffer, int offset) {
    int16_t a = 0;
    if (IsBigEndian()) {
        ((char*) &a)[0] = buffer[0 + offset];
        ((char*) &a)[1] = buffer[1 + offset];
    } else {
        ((char*) &a)[1] = buffer[0 + offset];
        ((char*) &a)[0] = buffer[1 + offset];
    }
    return a;
}
uint16_t cData::ByteToUint16(char *buffer, int offset) {
    uint16_t a = 0;
    if (IsBigEndian()) {
        ((char*) &a)[0] = buffer[0 + offset];
        ((char*) &a)[1] = buffer[1 + offset];
    } else {
        ((char*) &a)[1] = buffer[0 + offset];
        ((char*) &a)[0] = buffer[1 + offset];
    }
    return a;
}
float cData::ByteToFloat(char *buffer, int offset) {
    float a = 0;
    if (IsBigEndian()) {
        for(int i = 0; i < 4; i++)
            ((char*) &a)[i] = buffer[i + offset];
    } else {
        for(int i = 0; i < 4; i++)
            ((char*) &a)[3 - i] = buffer[i + offset];
    }
    return a;
}

void cData::Int32ToByte(int32_t &_int, char *dest) {
    if (IsBigEndian()) {
        dest[0] =  _int & 0x000000ff;
        dest[1] = (_int & 0x0000ff00) >> 8;
        dest[2] = (_int & 0x00ff0000) >> 16;
        dest[3] = (_int & 0xff000000) >> 24;
    } else {
        dest[3] =  _int & 0x000000ff;
        dest[2] = (_int & 0x0000ff00) >> 8;
        dest[1] = (_int & 0x00ff0000) >> 16;
        dest[0] = (_int & 0xff000000) >> 24;
    }
}
void cData::Uint32ToByte(uint32_t &_int, char *dest) {
    if (IsBigEndian()) {
        dest[0] =  _int & 0x000000ff;
        dest[1] = (_int & 0x0000ff00) >> 8;
        dest[2] = (_int & 0x00ff0000) >> 16;
        dest[3] = (_int & 0xff000000) >> 24;
    } else {
        dest[3] =  _int & 0x000000ff;
        dest[2] = (_int & 0x0000ff00) >> 8;
        dest[1] = (_int & 0x00ff0000) >> 16;
        dest[0] = (_int & 0xff000000) >> 24;
    }
}
void cData::Int16ToByte(int16_t &_short, char *dest) {
    if (IsBigEndian()) {
        dest[0] =  _short & 0x000000ff;
        dest[1] = (_short & 0x0000ff00) >> 8;
    } else {
        dest[1] =  _short & 0x000000ff;
        dest[0] = (_short & 0x0000ff00) >> 8;
    }
}
void cData::Uint16ToByte(uint16_t &_short, char *dest) {
    if (IsBigEndian()) {
        dest[0] =  _short & 0x000000ff;
        dest[1] = (_short & 0x0000ff00) >> 8;
    } else {
        dest[1] =  _short & 0x000000ff;
        dest[0] = (_short & 0x0000ff00) >> 8;
    }
}
void cData::FloatToByte(float &_float, char *dest) {
    uint32_t *tmpFloat = (uint32_t*)&_float;
    if (IsBigEndian()) {
        dest[0] =  *tmpFloat & 0x000000ff;
        dest[1] = (*tmpFloat & 0x0000ff00) >> 8;
        dest[2] = (*tmpFloat & 0x00ff0000) >> 16;
        dest[3] = (*tmpFloat & 0xff000000) >> 24;
    } else {
        dest[3] =  *tmpFloat & 0x000000ff;
        dest[2] = (*tmpFloat & 0x0000ff00) >> 8;
        dest[1] = (*tmpFloat & 0x00ff0000) >> 16;
        dest[0] = (*tmpFloat & 0xff000000) >> 24;
    }
}

void cData::ByteCopy(char *src, char *dest, int destOffset, int srcLen) {
    std::memcpy(dest + destOffset, src, srcLen);
}

} /* namespace StormFramework */