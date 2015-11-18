#include "eventsMain.h"
#include "cEventManager.h"

StormFramework::cEventManager eventManager;

int S_InitEventManager() {
    if (S_GetGraphicsApi() == -1) {
        return -1;
    }
    eventManager.SetApi(S_GetGraphicsApi());
    return 1;
}

StormFramework::cEventManager &S_GetEventManager() {
    return eventManager;
}

void S_TickEvents() {
    eventManager.Tick();
}