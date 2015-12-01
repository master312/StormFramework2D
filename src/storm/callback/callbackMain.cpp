#include "callbackMain.h"
#include "cCallbackManager.h"

StormFramework::cCallbackManager cbManager;

int S_InitCallbacks() {
    // Nothing here
    return 1;
}
uint32_t S_AddDelayedCB(StormCB *cb) {
    return cbManager.AddDelayedCallback(cb);
}
void S_AddIntervalCB(const std::string &name, StormCB *cb) {
    cbManager.AddIntervalCallback(name, cb);
}

void S_RemoveCB(const std::string &name) {
    cbManager.Remove(name);
}
void S_RemoveCB(uint32_t &id) {
    cbManager.Remove(id);
}

StormFramework::cCallbackManager &S_GetCallbackManager() {
    return cbManager;
}