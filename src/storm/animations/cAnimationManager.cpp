#include "cAnimationManager.h"

namespace StormFramework {

uint32_t cAnimationManager::Load(const std::string &filename) {
    cAnimation *anim = nullptr;
    
    auto iter = m_Animations.find(filename);
    if (iter == m_Animations.end()) {
        // Load and insert animation
        cAnimation tmp;
        if (tmp.Load(filename) < 0) {
            // Error is logged by cAnimation class
            return 0;
        }
        m_Animations[filename] = tmp;
        anim = &m_Animations[filename];
        m_AnimationsVec.push_back(anim);
    } else {
        anim = &iter->second;
    }
    uint32_t tmpId = anim->CreateAnimator();
    m_Animators[tmpId] = anim;
    return tmpId;
}
void cAnimationManager::Unload(uint32_t &id) {
    auto iter = m_Animators.find(id);
    if (iter == m_Animators.end()) {
        return;
    }

    cAnimation *tmpA = iter->second;
    m_Animators.erase(iter);
    // Animation will be automatically deleted if there are 
    // no any animators left using it
    tmpA->RemoveAnimator(id);
}
void cAnimationManager::DeleteObject(cAnimation *anim) {
    if (anim == nullptr)
        return;
    auto iter = m_Animations.find(anim->GetFilename());
    if (iter == m_Animations.end()) {
        return;
    }
    for (uint32_t i = 0; i < m_AnimationsVec.size(); i++) {
        if (m_AnimationsVec[i] == anim) {
            m_AnimationsVec.erase(m_AnimationsVec.begin() + i);
            break;
        }
    }
    S_LogDebug("cAnimationManager", 
               "Animation object '%s' deleted", anim->GetFilename().c_str());
    anim->Clear();
    m_Animations.erase(iter);
}
void cAnimationManager::Clear() {
    for (uint32_t i = 0; i < m_AnimationsVec.size(); i++) {
        m_AnimationsVec[i]->Clear();
    }
    m_Animators.clear();
    m_AnimationsVec.clear();
    m_Animations.clear();
}
void cAnimationManager::Tick(uint32_t &delta) {
#if STORM_ENABLE_ANIMATE_MANAGER != 0
    for (uint32_t i = 0; i < m_AnimationsVec.size(); i++) {
        m_AnimationsVec[i]->Tick(delta);
    }
#endif
}

} /* namespace StormFramework */