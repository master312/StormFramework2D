#include "callbackMain.h"
#include "cCallbackManager.h"

StormFramework::cCallbackManager cbManager;

int S_InitCallbacks() {
    // Nothing here
    return 1;
}
void S_AddDelayedCB(StormCB *cb) {
    cbManager.AddDelayedCallback(cb);
}
void S_AddIntervalCB(const std::string &name, StormCB *cb) {
    cbManager.AddIntervalCallback(name, cb);
}

void S_RemoveCB(const std::string &name) {
    cbManager.Remove(name);
}

StormFramework::cCallbackManager &S_GetCallbackManager() {
    return cbManager;
}