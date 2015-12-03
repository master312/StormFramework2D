#include "interruptsMain.h"
#include "cInterruptManager.h"

StormFramework::cInterruptManager cbManager;

int S_InitCallbacks() {
    // Nothing here
    return 1;
}
uint32_t S_AddDelayedCB(StormInterrupt *cb) {
    return cbManager.AddDelayedCallback(cb);
}
void S_CreateInterrupt(const std::string &name, StormInterrupt *cb) {
    cbManager.AddInterrupt(name, cb);
}

void S_RemoveCB(const std::string &name) {
    cbManager.Remove(name);
}
void S_RemoveCB(uint32_t &id) {
    cbManager.Remove(id);
}

StormFramework::cInterruptManager &S_GetCallbackManager() {
    return cbManager;
}