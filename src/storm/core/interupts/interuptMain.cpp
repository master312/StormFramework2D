#include "interuptMain.h"
#include "cInteruptManager.h"

StormFramework::cInteruptManager cbManager;

int S_InitCallbacks() {
    // Nothing here
    return 1;
}
uint32_t S_AddDelayedCB(StormInterupt *cb) {
    return cbManager.AddDelayedCallback(cb);
}
void S_CreateInterupt(const std::string &name, StormInterupt *cb) {
    cbManager.AddInterupt(name, cb);
}

void S_RemoveCB(const std::string &name) {
    cbManager.Remove(name);
}
void S_RemoveCB(uint32_t &id) {
    cbManager.Remove(id);
}

StormFramework::cInteruptManager &S_GetCallbackManager() {
    return cbManager;
}