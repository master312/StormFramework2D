/* 
 * File:   storm.h
 * Author: master312
 *
 * Created on November 08, 2015, 9:04 PM
 */

#ifndef SSTORM_H__
#define SSTORM_H__
#include "cMain.h"
#include "core/events/eventsMain.h"
#include "callback/callbackMain.h"
#include "animation/animationMain.h"

/* Initialize all elements of storm framework */
/* Graphics api must be set using 'S_SetGraphicsApi(...)'  */
/* before using this method */
// TODO: Error handling (return error ID)
int S_InitAll();

/* This method will start main loop. */
/* Everything should be initialized before using this method */
void S_StartMain();

void S_SetLogicTickLimit(uint32_t limit);
void S_SetGraphicsTickLimit(uint32_t limit);

uint32_t &GetDelta();

#endif /* SSTORM_H__ */