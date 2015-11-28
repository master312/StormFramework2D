/* 
 * File:   graphicsMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:36 PM
 */
 
#ifndef GRAPHICSMAIN_H__
#define GRAPHICSMAIN_H__
#include <iostream>
#include "../framework/frameworkMain.h"

namespace StormFramework { 
    class cGraphicsManager;
    class cTextureManager;
    class cBitmapFontManager;
}

void S_SetGraphicsApi(int api);
int S_GetGraphicsApi();

void S_InitGraphics();
void S_ClearScreen();
StormFramework::cGraphicsManager &S_GetGraphicsManager();
StormFramework::cTextureManager &S_GetTextureManager();
StormFramework::cBitmapFontManager &S_GetFontManager();

/**** Graphics object related methods ****/
// Creates new graphics object, and attach texture @filename to it
// It is safe to load same texture multiple times. It will be reused...
// @*id is raw texture ID, and should only be used for testing/debugging
uint32_t S_CreateGraphics(const std::string &filename, uint32_t *id = nullptr);
void S_DestroyGraphics(uint32_t id);
/* Graphics object parameter modifying methods */
void S_GraphModVisible(uint32_t id, bool isVisible);
void S_GraphModPos(uint32_t id, sPoint &point);
void S_GraphModPos(uint32_t id, int x, int y);
void S_GraphModZ(uint32_t id, int z);
void S_GraphModAngle(uint32_t id, double angle);
void S_GraphModOpacity(uint32_t id, uint8_t opacity);
void S_GraphModCenter(uint32_t id, sPoint &center);
void S_GraphModCenter(uint32_t id, int x, int y);
sRect &S_GraphGetPos(uint32_t id);    //TODO: Maby nullptr check ?
int &S_GraphGetZ(uint32_t id);
bool S_GraphIsVisible(uint32_t id);
double &S_GraphGetAngle(uint32_t id);
uint8_t &S_GraphGetOpacity(uint32_t id);
sPoint &S_GraphGetCenter(uint32_t id);
/* Raw texture related methods 
 * These texture drawing methods should not be used
 * These are only planned for internal use/testing */
//uint32_t S_Load
void S_ModColorRaw(uint32_t id, uint8_t r, uint8_t g, uint8_t b);
void S_DrawRaw(uint32_t &id, sRect &src, int &x, int &y);
void S_DrawRaw(uint32_t &id, int &x, int &y);
uint32_t S_GetRawTextureWidth(uint32_t id);
uint32_t S_GetRawTextureHeight(uint32_t id);
/**** Texture section related methods ****/
uint32_t S_CreateSection(const std::string &filename, sRect &section);
uint32_t S_CreateSection(uint32_t &id, sRect &section);
/**** Font manager ****/
bool S_LoadFont(const std::string &filename);
void S_UnlaodFont(const std::string &fontName);
void S_DrawText(const std::string &text, int x, int y, 
                   uint8_t r = 0, uint8_t g = 0, 
                   uint8_t b = 0, uint8_t a = 255,
                   const std::string &fontName = "default");
void S_RefDrawText(const std::string &text, int &x, int &y, 
                   uint8_t &r, uint8_t &g, 
                   uint8_t &b, uint8_t &a,
                   const std::string &fontName);

#endif
