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

// Uncomment libraries you want to build
//#define STORM_BUILD_SDL 1
#define STORM_BUILD_SDL2 1
#define STORM_BUILD_GLES 1

// Define storm framework version
#define STORM_VERSION_MAJOR 0
#define STORM_VERSION_MINOR 32
#define STORM_VERSION_FIX 9

#define STORM_API_SDL 1
#define STORM_API_SDL2 2
#define STORM_API_GLES 3

#define STORM_DIR_DATA "data/"
#define STORM_DIR_GRAPHICS "data/graphics/"
#define STORM_DIR_FONTS "data/fonts/"
#define STORM_DIR_ANIMATIONS "data/animations/"

#define STORM_TEXTURE_TIMEOUT 10000  //Delete texture if unused for this time(ms)
#define STORM_ANIMATION_MAX_FPS 30   //Maximum FPS that animation can have

// It this is set to zero, graphics will not be drawn
// automatically on load. It has to be drawn manually every frame
#define STORM_ENABLE_DRAW_MANAGER 1
// It this is set to zero, animation will not tick
#define STORM_ENABLE_ANIMATE_MANAGER 1

#endif /* STORM_DEFINES_H__ */