#include "statesMain.h"

StormFramework::cStateManager stateManager;

void S_InitStateManager() {
	// Nothing here yet...
}

void S_PushState(StormState *state) {
	stateManager.PushState(state);
}

StormFramework::cStateManager &S_GetStateManager() {
	return stateManager;
}