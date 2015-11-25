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
    textureManager.Initialize();
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

uint32_t S_LoadTexture(const std::string &filename, 
                       uint32_t *id /* = nullptr */) {
    return graphicsManager.LoadTexture(filename, id);
}
void S_UnloadTexture(uint32_t id) {
    graphicsManager.UnloadTexture(id);
}
void S_TextureModVisible(uint32_t id, bool isVisible) {
    graphicsManager.TxtModVisible(id, isVisible);
}
void S_TextureModPos(uint32_t id, sPoint &point) {
    graphicsManager.TxtModPos(id, point);
}
void S_TextureModPos(uint32_t id, int x, int y) {
    graphicsManager.TxtModPos(id, x, y);
}
void S_TextureModZ(uint32_t id, int z) {
    graphicsManager.TxtModZ(id, z);
}
void S_TextureModColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b) {
    textureManager.GetTexture(id)->ModColor(r, g, b);
}
void S_TextureModAngle(uint32_t id, double angle) {
    graphicsManager.TxtModAngle(id, angle);
}
void S_TextureModOpacity(uint32_t id, uint8_t opacity) {
    graphicsManager.TxtModOpacity(id, opacity);
}
void S_TextureModCenter(uint32_t id, sPoint &center) {
    graphicsManager.TxtModCenter(id, center);
}
void S_TextureModCenter(uint32_t id, int x, int y) {
    graphicsManager.TxtModCenter(id, x, y);
}
sRect &S_TextureGetPos(uint32_t id) {
    return graphicsManager.GetObject(id)->m_DestRect;
}
int &S_TextureGetZ(uint32_t id) {
   return graphicsManager.GetObject(id)->m_Z;
}
bool S_TextureIsVisible(uint32_t id) {
    return graphicsManager.GetObject(id)->m_IsVisible;
}
double &S_TextureGetAngle(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Angle;
}
uint8_t &S_TextureGetOpacity(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Opacity;
}
sPoint &S_TextureGetCenter(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Center;
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

uint32_t S_CreateSection(const std::string &filename , sRect &section) {
    return graphicsManager.CreateSection(filename, section);
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


