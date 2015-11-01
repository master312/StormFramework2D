/* 
 * File:   defines.h
 * Author: master312
 *
 * Created on October 18, 2015, 4:41 PM
 */

#ifndef STORM_DEFINES_H__
#define STORM_DEFINES_H__

#ifdef _WIN32
#define OS_WINDOWS 1
#include <cstdarg>
typedef unsigned int uint;
#elif __linux 
#define OS_LINUX 1
#elif __mac_os_x
//TODO: Mac support
#endif

#define STORM_BUILD_SDL 0
#define STORM_BUILD_SDL2 1
#define STORM_BUILD_GLES 0

#define STORM_VERSION_MAJOR 0
#define STORM_VERSION_MINOR 20
#define STORM_VERSION_FIX 1

#define STORM_API_SDL 1
#define STORM_API_SDL2 2
#define STORM_API_GLES 3

#define STORM_DIR_DATA "data/"
#define STORM_DIR_GRAPHICS "data/graphics/"

#endif /* STORM_DEFINES_H__ */