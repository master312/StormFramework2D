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

uint32_t S_CreateGraphics(const std::string &filename, 
                       uint32_t *id /* = nullptr */) {
    return graphicsManager.CreateObject(filename, id);
}
void S_DestroyGraphics(uint32_t id) {
    graphicsManager.DestroyObject(id);
}
void S_GraphModVisible(uint32_t id, bool isVisible) {
    graphicsManager.GraphModVisible(id, isVisible);
}
void S_GraphModPos(uint32_t id, sPoint &point) {
    graphicsManager.GraphModPos(id, point);
}
void S_GraphModPos(uint32_t id, int x, int y) {
    graphicsManager.GraphModPos(id, x, y);
}
void S_GraphModZ(uint32_t id, int z) {
    graphicsManager.GraphModZ(id, z);
}
void S_GraphModAngle(uint32_t id, double angle) {
    graphicsManager.GraphModAngle(id, angle);
}
void S_GraphModOpacity(uint32_t id, uint8_t opacity) {
    graphicsManager.GraphModOpacity(id, opacity);
}
void S_GraphModCenter(uint32_t id, sPoint &center) {
    graphicsManager.GraphModCenter(id, center);
}
void S_GraphModCenter(uint32_t id, int x, int y) {
    graphicsManager.GraphModCenter(id, x, y);
}
void S_GraphModSize(uint32_t id, uint32_t w, uint32_t h) {
    graphicsManager.GraphModSize(id, w, h);
}
sRect &S_GraphGetPos(uint32_t id) {
    return graphicsManager.GetObject(id)->m_DestRect;
}
int &S_GraphGetZ(uint32_t id) {
   return graphicsManager.GetObject(id)->m_Z;
}
bool S_GraphIsVisible(uint32_t id) {
    return graphicsManager.GetObject(id)->m_IsVisible;
}
double &S_GraphGetAngle(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Angle;
}
uint8_t &S_GraphGetOpacity(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Opacity;
}
sPoint &S_GraphGetCenter(uint32_t id) {
    return graphicsManager.GetObject(id)->m_Center;
}
/* *********** raw texture methods ******** */
void S_ModColorRaw(uint32_t id, uint8_t r, uint8_t g, uint8_t b) {
    textureManager.GetTexture(id)->ModColor(r, g, b);
}
void S_DrawRaw(uint32_t &id, sRect &src, int &x, int &y) {
    textureManager.Draw(id, src, x, y);
}
void S_DrawRaw(uint32_t &id, int &x, int &y) {
    textureManager.Draw(id, x, y);
}
uint32_t S_GetRawTextureWidth(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager.GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetPxWidth();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}
uint32_t S_GetRawTextureHeight(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager.GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetPxWidth();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}
/* **************************************** */
uint32_t S_CreateSection(const std::string &filename , sRect &section) {
    return graphicsManager.CreateSection(filename, section);
}
uint32_t S_CreateSection(uint32_t &id, sRect &section) {
    return graphicsManager.CreateSection(id, section);
}
void S_GraphModSrc(uint32_t &id, sRect &src) {
    graphicsManager.GetObject(id)->m_SrcRect = src;
}
sRect *S_GraphGetSrc(uint32_t &id) {
    return &graphicsManager.GetObject(id)->m_SrcRect;
}
uint32_t S_CreateGeometry(StormGeometry *geometry) {
    return graphicsManager.CreateGeometry(geometry);
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


