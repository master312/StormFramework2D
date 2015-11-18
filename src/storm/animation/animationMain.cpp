#include "animationMain.h"


StormFramework::cAnimationManager animationManager;

void S_InitAnimations() {
    // Nothing here, but something may be put here
}

uint32_t S_LoadAnimation(const std::string &filename) {
    return animationManager.Load(filename);
}
void S_UnloadAnimation(uint32_t id) {
    animationManager.Unload(id);
}

uint32_t S_AddAnimation(StormAnimation anim, const std::string &filename) {
    return animationManager.Add(anim, filename);
}

StormAnimation *S_GetAnimation(uint32_t id) {
    return animationManager.GetAnimation(id);
}
StormAnimation *S_GetAnimation(const std::string &filename) {
    return animationManager.GetAnimation(filename);
}

uint32_t S_CreateAnimator(uint32_t animationId) {
    return animationManager.CreateAnimator(animationId);
}
void S_RemoveAnimator(uint32_t animationId, uint32_t animatorId) {
    animationManager.RemoveAnimatior(animatorId, animationId);
}
StormAnimator *S_GetAnimator(uint32_t animationId, uint32_t animatorId) {
    return animationManager.GetAnimator(animationId, animatorId);
}

void S_RefDrawAnimation(uint32_t &animationId, uint32_t &animatorId, 
                        int &x, int &y) {
    animationManager.Draw(animationId, animatorId, x, y);
}

void S_DrawAnimation(uint32_t animationId, uint32_t animatorId, 
                     int x, int y) {
    animationManager.Draw(animationId, animatorId, x, y);
}

StormFramework::cAnimationManager &S_GetAnimationManager() {
    return animationManager;
}