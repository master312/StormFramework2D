/* 
 * File:   cAnimationManager.h
 * Author: master312
 *
 * Created on October 28, 2015, 7:59 PM
 * Every animation have its own file with unique filename and path
 * That is how we know should we create new animator, or load whole animation 

 */

#ifndef CANIMATIONMANAGER_H__
#define CANIMATIONMANAGER_H__
#include <iostream>
#include <map>
#include <vector>
#include "cAnimation.h"

namespace StormFramework {

class cAnimationManager {
public:
    /* Loads animation and returns new animator ID
     * If animation is already loaded, if will not 
     * be loaded again. New instance will be created 
     * in that case */
    uint32_t Load(const std::string &filename);
    void Unload(uint32_t &id);

    /* Tick all animations */
    void Tick(uint32_t &delta);

    sAnimator *GetAnimator(uint32_t &id) {
        auto iter = m_Animators.find(id);
        if (iter == m_Animators.end()) {
            return nullptr;
        }
        return iter->second->GetAnimator(id);
    }

    uint32_t GetAnimatorCount() { return m_Animators.size(); }
    uint32_t GetAnimationCount() { return m_Animations.size(); }
public:
    /* Map of all animator id's 
     * <animatorId, pointerToAnimation> */
    std::map<uint32_t, cAnimation*> m_Animators;
    /* Map of all animation objects, indexed by names */
    std::map<std::string, cAnimation> m_Animations;
    /* Vector of all animations used for iterating optimization */
    std::vector<cAnimation*> m_AnimationsVec;
};

} /* namespace StormFramework */
#endif /* CANIMATIONMANAGER_H__ */