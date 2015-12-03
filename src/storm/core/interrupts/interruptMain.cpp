#include "interruptMain.h"
#include "cInterruptManager.h"

StormFramework::cinterruptManager cbManager;

int S_InitCallbacks() {
    // Nothing here
    return 1;
}
uint32_t S_AddDelayedCB(Storminterrupt *cb) {
    return cbManager.AddDelayedCallback(cb);
}
void S_Createinterrupt(const std::string &name, Storminterrupt *cb) {
    cbManager.Addinterrupt(name, cb);
}

void S_RemoveCB(const std::string &name) {
    cbManager.Remove(name);
}
void S_RemoveCB(uint32_t &id) {
    cbManager.Remove(id);
}

StormFramework::cinterruptManager &S_GetCallbackManager() {
    return cbManager;
}