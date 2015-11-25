/* 
 * File:   eventsMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 8:27 PM
 */

#ifndef EVENTSMAIN_H__
#define EVENTSMAIN_H__
#include "../graphics/graphicsMain.h"
#include "eStormKeys.h"

namespace StormFramework { class cEventManager; }

int S_InitEventManager();
StormFramework::cEventManager &S_GetEventManager();

/* Adds new handler function callback to events manager */
//void S_AddEventHandler(cStormCallbacker *cb, std::string name);
/* Removes handler function from event manager */
/* void S_RemoveEventHandler(std::string name); */
/* Return true if key is pressed */
bool S_IsKeyDown(StormKey key);
/* Return true if key is not pressed */
bool S_IsKeyUp(StormKey key);
/* Return mouse coordinates */
sPoint &S_GetMouseLoc();
/* Return amount of mouse scroll. */
int S_GetMouseScroll();
/* Return mouse buttons states */
bool S_IsMouseLeft();
bool S_IsMouseRight();
bool S_IsMouseMiddle();
/* Start scanning for text input */
void S_StartTextInput();
/* Stop scanning for text input */
void S_StopTextInput();
/* Return true if text input is enabled */
bool S_IsTextInput();
/* Returns inputed string; */
std::string &S_GetTextInput();
/* Set text to be edited by text inputing system */
void S_SetTextInput(const std::string &text);

#endif /* EVENTSMAIN_H__ */