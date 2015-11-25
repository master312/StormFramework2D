/* 
 * File:   callbackMain.h
 * Author: master312
 *
 * Created on November 17, 2015, 6:50 PM
 */

#ifndef SCALLBACKMAIN_H__
#define SCALLBACKMAIN_H__
#include <iostream>
#include "sCallback.h"

typedef StormFramework::sCallback StormCB;

namespace StormFramework {
    class cCallbackManager;
}

/* Initialize callback system */
int S_InitCallbacks();;
/* Callback method will be called only once after specified delay */
void S_AddDelayedCB(StormCB *cb);
/* Callback method will be called on specified interval */
/* If method returns < 0, it will be removed from callback system */
void S_AddIntervalCB(const std::string &name, StormCB *cb);

void S_RemoveCB(const std::string &name);


StormFramework::cCallbackManager &S_GetCallbackManager();

#endif /* SCALLBACKMAIN_H__ */