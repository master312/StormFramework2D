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

    return anim->CreateAnimator();
}
void cAnimationManager::Unload(uint32_t &id) {
    auto iter = m_Animators.find(id);
    if (iter == m_Animators.end()) {
        return;
    }

    cAnimation *tmpA = iter->second;
    m_Animators.erase(iter);
    tmpA->RemoveAnimator(id);

    if (tmpA->CountAnimators() <= 0) {
        // Animation not in use. Delete it
        for (uint32_t i = 0; i < m_AnimationsVec.size(); i++) {
            if (m_AnimationsVec[i] == tmpA) {
                m_AnimationsVec.erase(m_AnimationsVec.begin() + i);
                break;
            }
        }

        tmpA->Clear();
        m_Animations.erase(tmpA->GetFilename());
    }
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
    for (uint32_t i = 0; i < m_AnimationsVec.size(); i++) {
        m_AnimationsVec[i]->Tick(delta);
    }
}

} /* namespace StormFramework */