/* 
 * File:   cAnimationManager.h
 * Author: master312
 *
 * Created on October 28, 2015, 7:59 PM
 */

#ifndef CANIMATIONMANAGER_H__
#define CANIMATIONMANAGER_H__
#include <iostream>
#include <map>
#include "cAnimation.h"

namespace StormFramework {

class cAnimationManager {
public:
    cAnimationManager();

    /* Loads animation from file. Returns 0 on error */
    uint32_t Load(const std::string &filename);
    /* Unloads animation */
    void Unload(uint32_t animationId);

    /* Adds animation object to manager */
    /* Returns animation id, or 0 on error */
    uint32_t Add(cAnimation anim, const std::string &filename);
    /* Return pointer to cAnimation object, or nullptr if not found */
    cAnimation *GetAnimation(uint32_t id);
    cAnimation *GetAnimation(const std::string &filename);


    /* Creates new animator for @animationId */
    /* Returns it's id, or 0 on error */
    uint32_t CreateAnimator(uint32_t animationId);
    /* Removes @animatorId form @animationId */
    void RemoveAnimatior(uint32_t animationId, uint32_t animatorId);
    // TODO: Animator control methods here
    /* Returns pointer to animator object, or nulltpr if not found */
    sAnimator *GetAnimator(uint32_t animationId, uint32_t animatorId);

    void Draw(uint32_t &animationId, uint32_t &animatorId, int &x, int &y);
    void Draw(uint32_t &animationId, uint32_t &animatorId, 
              int &x, int &y, int &w, int &h) { }

    void Tick();

    /* If this is set to true, all animation that */
    /* have no animator, and are unused for specified time */
    /* will be deleted */
    // TODO: ...
    void SetAutoUnload(bool isAuto) { }
private:
    /* Map of all animation */
    std::map<uint32_t, cAnimation> m_Animations;
    std::map<std::string, uint32_t> m_Filenames;

    bool m_IsAutoUnload;    // TODO ...
};

} /* namespace StormFramework */
#endif /* CANIMATIONMANAGER_H__ */