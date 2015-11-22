/* 
 * File:   layersMain.h
 * Author: master312
 *
 * Created on November 02, 2015, 7:01 PM
 */

#ifndef LAYERSMAIN_H__
#define LAYERSMAIN_H__
#include "cLayerBase.h"
#include "cLayerManager.h"

typedef StormFramework::cLayerBase StormLayer;

void S_InitLayerManager();
void S_PushLayer(StormLayer *state);
StormFramework::cLayerManager &S_GetLayerManager();

#endif /* LAYERSMAIN_H__ */