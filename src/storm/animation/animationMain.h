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
typedef StormFramework::sAnimator StormAnimator;

void S_InitAnimations();
StormFramework::cAnimationManager &S_GetAnimationManager();

uint32_t S_LoadAnimation(const std::string &filename);
void S_UnloadAnimation(uint32_t &id);

StormAnimator *S_GetAnimator(uint32_t &id);

#endif /* ANIMATIONMAIN_H__ */