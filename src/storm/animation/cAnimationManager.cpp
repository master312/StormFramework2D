#include "cAnimationManager.h"

namespace StormFramework {

cAnimationManager::cAnimationManager() : m_IsAutoUnload(false) {
}

uint32_t cAnimationManager::Load(const std::string &filename) {
    auto iter = m_Filenames.find(filename);
    if (iter != m_Filenames.end()){
        // Animation with this filename is already loaded
        return iter->second;
    }

    cAnimation tmpAnim;
    if (!tmpAnim.Load(filename)) {
        return 0;
    }

    return Add(tmpAnim, filename);
}
void cAnimationManager::Unload(uint32_t animationId) {
    auto iter = m_Animations.find(animationId);

    if (iter == m_Animations.end()) {
        return;
    }

    m_Animations.erase(iter);

    for (auto &iter : m_Filenames) {
        if (iter.second == animationId) {
            m_Filenames.erase(iter.first);
            return;
        }
    }
}

uint32_t cAnimationManager::Add(cAnimation anim, const std::string &filename) {
    uint32_t tmpId;
    
    if (m_Animations.size() > 0) {
        auto iter = m_Animations.end();
        --iter;
        tmpId = iter->first + 1;
    } else {
        tmpId = 1;
    }

    m_Animations[tmpId] = anim;
    m_Filenames[filename] = tmpId;

    return tmpId;
}
cAnimation *cAnimationManager::GetAnimation(uint32_t id) {
    auto iter = m_Animations.find(id);
    if (iter != m_Animations.end()) {
        return &iter->second;
    }
    return nullptr;
}
cAnimation *cAnimationManager::GetAnimation(const std::string &filename) {
    auto iter = m_Filenames.find(filename);
    if (iter != m_Filenames.end()) {
        cAnimation *tmpAnim = &m_Animations[iter->second];
        return tmpAnim;
    }
    return nullptr;
}

uint32_t cAnimationManager::CreateAnimator(uint32_t animationId) {
    cAnimation *tmp = GetAnimation(animationId);
    if (tmp == nullptr) { 
        return 0; 
    }
    return tmp->CreateAnimator();
}
void cAnimationManager::RemoveAnimatior(uint32_t animationId, 
                                        uint32_t animatorId) {
    cAnimation *tmp = GetAnimation(animationId);
    if (tmp == nullptr) { 
        return;
    }
    tmp->RemoveAnimatior(animatorId);
}
sAnimator *cAnimationManager::GetAnimator(uint32_t animationId, 
                                          uint32_t animatorId) {
    cAnimation *tmp = GetAnimation(animationId);
    if (tmp == nullptr) { 
        return nullptr;
    }
    return tmp->GetAnimator(animatorId);
}

void cAnimationManager::Draw(uint32_t &animationId, uint32_t &animatorId, 
                             int &x, int &y) {
    cAnimation *tmp = GetAnimation(animationId);
    if (tmp == nullptr) { 
        S_LogWarning("cAnimationManager", 
                    "Trying to draw non existing animation ID:%d", animationId);
        return;
    }
    tmp->Draw(animatorId, x, y);   
}

void cAnimationManager::Tick() {
    for (auto &iter : m_Animations) {
        iter.second.Tick();
    }
}

} /* namespace StormFramework */