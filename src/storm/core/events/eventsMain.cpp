#include "eventsMain.h"
#include "cEventManager.h"

StormFramework::cEventManager *eventManager = nullptr;

int S_InitEventManager() {
    if (S_GetGraphicsApi() == -1) {
        return -1;
    }
    eventManager = new StormFramework::cEventManager(S_GetGraphicsApi());
    return 1;
}

StormFramework::cEventManager *S_GetEventManager() {
    return eventManager;
}

void S_TickEvents() {
    eventManager->Tick();
}