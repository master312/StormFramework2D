/* 
 * File:   eventsMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 8:27 PM
 */

#ifndef EVENTSMAIN_H__
#define EVENTSMAIN_H__
#include "../graphics/graphicsMain.h"

namespace StormFramework { class cEventManager; }

int S_InitEventManager();
StormFramework::cEventManager *S_GetEventManager();
void S_TickEvents();

#endif /* EVENTSMAIN_H__ */