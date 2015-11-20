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
bool S_TickGraphics();
void S_DeleteGraphics();
StormFramework::cGraphicsManager &S_GetGraphicsManager();
StormFramework::cTextureManager &S_GetTextureManager();
StormFramework::cBitmapFontManager &S_GetFontManager();

/**** Texture related methods ****/
uint32_t S_LoadTexture(const std::string &filename);
void S_UnloadTexture(uint32_t id);
void S_DrawTexture(uint32_t id, int x, int y);
void S_RefDrawTexture(uint32_t &id, sRect &src, int &x, int &y);
void S_RefDrawTexture(uint32_t &id, int &x, int &y);
uint32_t S_GetTextureWidth(uint32_t id);
uint32_t S_GetTextureHeight(uint32_t id);
/* Texture parameter modifying methods */
void S_TextureModVisible(uint32_t id, bool isVisible);
void S_TextureModPos(uint32_t id, sPoint &point);
void S_TextureModPos(uint32_t id, int x, int y);
void S_TextureModColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b);
void S_TextureModAngle(uint32_t id, double angle);
void S_TextureModOpacity(uint32_t id, uint8_t opacity);
void S_TextureModCenter(uint32_t id, sPoint &center);
void S_TextureModCenter(uint32_t id, int x, int y);
/**** Texture section related methods ****/
uint32_t S_CreateSection(uint32_t textureId, sRect &section);
void S_RemoveSection(uint32_t &sectionId);
void S_DrawSection(uint32_t &sectionId, int x, int y);
void S_RefDrawSection(uint32_t &sectionId, int &x, int &y);
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
