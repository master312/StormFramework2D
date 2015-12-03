/* 
 * File:   interuptMain.h
 * Author: master312
 *
 * Created on November 17, 2015, 6:50 PM
 */

#ifndef SCALLBACKMAIN_H__
#define SCALLBACKMAIN_H__
// New interrupt macro, t-time,c-class,m-method(function),o-object
#define STORM_INTERUPT(t, c, m, o) StormInterupt(t, std::bind(&c::m, o))
#include <iostream>
#include <functional>
#include "sInterupt.h"

typedef StormFramework::sInterupt StormInterupt;

namespace StormFramework {
    class cInteruptManager;
}

/* Initialize callback system */
int S_InitCallbacks();;
/* Callback method will be called only once after specified delay */
/* Return 'ID' of callback, so it can be canceled later */
uint32_t S_AddDelayedCB(StormInterupt *cb);
/* Callback method will be called on specified interval */
/* If method returns < 0, it will be removed from callback system */
void S_CreateInterupt(const std::string &name, StormInterupt *cb);

void S_RemoveCB(const std::string &name);
void S_RemoveCB(uint32_t &id);

StormFramework::cInteruptManager &S_GetCallbackManager();

#endif /* SCALLBACKMAIN_H__ */