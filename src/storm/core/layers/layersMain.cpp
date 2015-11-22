#include "layersMain.h"

StormFramework::cLayerManager layerManager;

void S_InitLayerManager() {
	layerManager.Init();
}

void S_PushLayer(StormLayer *state) {
	layerManager.PushLayer(state);
}

StormFramework::cLayerManager &S_GetLayerManager() {
	return layerManager;
}