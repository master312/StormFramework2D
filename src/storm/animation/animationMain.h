/* 
 * File:   animationMain.h
 * Author: master312
 *
 * Created on October 28, 2015, 9:47 PM
 */
#ifndef ANIMATIONMAIN_H__
#define ANIMATIONMAIN_H__
#include "cAnimationManager.h"

typedef StormFramework::cAnimation StormAnimation;

void S_InitAnimations();

uint32_t S_LoadAnimation(const std::string &filename);
void S_UnloadAnimation(uint32_t id);

uint32_t S_AddAnimation(StormAnimation anim, const std::string &filename);

StormAnimation *S_GetAnimation(uint32_t id);
StormAnimation *S_GetAnimation(const std::string &filename);

uint32_t S_CreateAnimator(uint32_t animationId);
void S_RemoveAnimator(uint32_t animationId, uint32_t animatorId);
StormFramework::sAnimator*
S_GetAnimator(uint32_t animationId, uint32_t animatorId);

void S_RefDrawAnimation(uint32_t &animationId, uint32_t &animatorId, 
                        int &x, int &y);
void S_DrawAnimation(uint32_t animationId, uint32_t animatorId, 
                     int x, int y);

StormFramework::cAnimationManager *S_GetAnimationManager();

#endif /* ANIMATIONMAIN_H__ */