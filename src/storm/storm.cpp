#include "storm.h"

StormFramework::cMain stormMain;

int S_InitAll() {
    StormFramework::cTime::Start();
    S_InitCallbacks();
    S_InitGraphics();
    S_InitEventManager();
    S_InitLayerManager();
    S_LogInfo("storm", "Framework initialized!");
    return 1;
}

void S_StartMain() {
    STORM_SLEEP(10);
    stormMain.Start();
}

void S_SetLogicTickLimit(uint32_t limit) {
    stormMain.SetLogicTickLimit(limit);
}
void S_SetGraphicsTickLimit(uint32_t limit) {
    stormMain.SetGraphicsTickLimit(limit);
}

uint32_t &GetDelta() {
    return stormMain.GetDelta();
}