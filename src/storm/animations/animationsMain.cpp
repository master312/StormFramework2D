#include "animationsMain.h"
#include "cAnimationManager.h"

StormFramework::cAnimationManager animManager;

void S_InitAnimations() {
    // Nothing here, but something may be put here
}

StormFramework::cAnimationManager &S_GetAnimationManager() {
    return animManager;
}

uint32_t S_LoadAnimation(const std::string &filename) {
    return animManager.Load(filename);
}

StormAnimator *S_GetAnimator(uint32_t &id) {
    return animManager.GetAnimator(id);
}