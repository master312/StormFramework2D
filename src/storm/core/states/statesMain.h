/* 
 * File:   statesMain.h
 * Author: master312
 *
 * Created on November 02, 2015, 7:01 PM
 */

#ifndef STATESMAIN_H__
#define STATESMAIN_H__
#include "cStateBase.h"
#include "cStateManager.h"

typedef StormFramework::cStateBase StormState;

void S_InitStateManager();
void S_PushState(StormState *state);
StormFramework::cStateManager &S_GetStateManager();

#endif /* STATESMAIN_H__ */