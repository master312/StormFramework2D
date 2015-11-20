#include "graphicsMain.h"
#include "cGraphicsManager.h"
#include "cTextureManager.h"
#include "cBitmapFontManager.h"

int graphicsApi = -1;
StormFramework::cGraphicsManager graphicsManager;
StormFramework::cTextureManager textureManager;
StormFramework::cBitmapFontManager fontManager;


void S_SetGraphicsApi(int api) {
    graphicsApi = api;
}
int S_GetGraphicsApi() {
    return graphicsApi;
}
void S_InitGraphics() {
    if (graphicsApi == -1){
        S_LogError("GraphicsMain", "Graphics API not set!");
        return;
    }
    graphicsManager.Initialize();
}

bool S_TickGraphics() {
    return graphicsManager.Tick();
}
void S_ClearScreen() {
    graphicsManager.GetGraphics()->ClearScreen();
}
StormFramework::cGraphicsManager &S_GetGraphicsManager() {
    return graphicsManager;
}
StormFramework::cTextureManager &S_GetTextureManager() {
    return textureManager;
}
StormFramework::cBitmapFontManager &S_GetFontManager() {
    return fontManager;
}

uint32_t S_LoadTexture(const std::string &filename) {
    return textureManager.Load(filename);
}
void S_UnloadTexture(uint32_t id) {
    textureManager.Unload(id);
}
void S_DrawTexture(uint32_t id, int x, int y) {
    textureManager.Draw(id, x, y);
}
void S_RefDrawTexture(uint32_t &id, sRect &src, int &x, int &y) {
    textureManager.Draw(id, src, x, y);
}
void S_RefDrawTexture(uint32_t &id, int &x, int &y) {
    textureManager.Draw(id, x, y);
}
uint32_t S_GetTextureWidth(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager.GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetWidthPx();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}
uint32_t S_GetTextureHeight(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager.GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetWidthPx();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}
void S_TextureModVisible(uint32_t id, bool isVisible) {
    textureManager.ModVisible(id, isVisible);
}
void S_TextureModPos(uint32_t id, sPoint &point) {
    textureManager.ModPos(id, point);
}
void S_TextureModPos(uint32_t id, int x, int y) {
    textureManager.ModPos(id, x, y);
}
void S_TextureModColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b) {
    textureManager.GetTexture(id)->ModColor(r, g, b);
}
void S_TextureModAngle(uint32_t id, double angle) {
    textureManager.ModAngle(id, angle);
}
void S_TextureModOpacity(uint32_t id, uint8_t opacity) {
    textureManager.ModOpacity(id, opacity);
}
void S_TextureModCenter(uint32_t id, sPoint &center) {
    textureManager.ModCenter(id, center);
}
void S_TextureModCenter(uint32_t id, int x, int y) {
    textureManager.ModCenter(id, x, y);
}

uint32_t S_CreateSection(uint32_t textureId, sRect &section) {
    return textureManager.CreateSection(textureId, section);
}
void S_RemoveSection(uint32_t &sectionId) {
    textureManager.RemoveSection(sectionId);
}
void S_DrawSection(uint32_t &sectionId, int x, int y) {
    textureManager.DrawSection(sectionId, x, y);
}
void S_RefDrawSection(uint32_t &sectionId, int &x, int &y) {
    textureManager.DrawSection(sectionId, x, y);
}

bool S_LoadFont(const std::string &filename) {
    return fontManager.LoadFont(filename);
}
void S_UnlaodFont(const std::string &fontName) {
    fontManager.UnloadFont(fontName);
}
void S_DrawText(const std::string &text, int x, int y, 
                   uint8_t r /* = 0 */, uint8_t g /* = 0 */, 
                   uint8_t b /* = 0 */, uint8_t a /* = 255 */,
                   const std::string &fontName /* = "default" */) {
    fontManager.DrawText(text, x, y, r, g, b, a, fontName);
}
void S_RefDrawText(const std::string &text, int &x, int &y, 
                uint8_t &r /* = 0 */, uint8_t &g /* = 0 */, 
                uint8_t &b /* = 0 */, uint8_t &a /* = 255 */,
                const std::string &fontName /* = "default" */) {
    fontManager.DrawText(text, x, y, r, g, b, a, fontName);
}


