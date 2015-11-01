#include "graphicsMain.h"
#include "cGraphicsManager.h"
#include "cTextureManager.h"

int graphicsApi = -1;
StormFramework::cGraphicsManager *graphicsManager = nullptr;
StormFramework::cTextureManager *textureManager = nullptr;


void S_SetGraphicsApi(int api) {
    graphicsApi = api;
}
int S_GetGraphicsApi() {
    return graphicsApi;
    delete textureManager;
}
void S_InitGraphics() {
    if (graphicsApi == -1){
        S_LogError("GraphicsMain", "Graphics API not set!");
        return;
    }
    graphicsManager = new StormFramework::cGraphicsManager();
    graphicsManager->Initialize();
    textureManager = new StormFramework::cTextureManager();
}

bool S_TickGraphics() {
    return graphicsManager->Tick();
}
void S_ClearScreen() {
    graphicsManager->GetGraphics()->ClearScreen();
}
void S_DeleteGraphics() {
    delete graphicsManager;
}
StormFramework::cGraphicsManager *GetGraphicsManager() {
    return graphicsManager;
}

uint32_t S_LoadTexture(const std::string &filename) {
    return textureManager->Load(filename);
}
void S_UnloadTexture(uint32_t id) {
    textureManager->Unload(id);
}
void S_DrawTexture(uint32_t id, int x, int y) {
    textureManager->Draw(id, x, y);
}
void S_RefDrawTexture(uint32_t &id, int &x, int &y) {
    textureManager->Draw(id, x, y);
}
uint32_t S_GetTextureWidth(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager->GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetWidthPx();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}
uint32_t S_GetTextureHeight(uint32_t id) {
    StormFramework::cTextureBase *tmp = textureManager->GetTexture(id);
    if (tmp != nullptr) {
        return tmp->GetWidthPx();
    }
    S_LogError("graphicsMain.cpp", "Could not found texture id: '%d'", id);
    return 0;
}

uint32_t S_CreateSection(uint32_t textureId, sRect &section) {
    return textureManager->CreateSection(textureId, section);
}
void S_RemoveSection(uint32_t sectionId) {
    textureManager->RemoveSection(sectionId);
}
void S_DrawSection(uint32_t sectionId, int x, int y) {
    textureManager->DrawSection(sectionId, x, y);
}
void S_RefDrawSection(uint32_t &sectionId, int &x, int &y) {
    textureManager->DrawSection(sectionId, x, y);
}