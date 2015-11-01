#include "cAnimation.h"

namespace StormFramework {

cAnimation::cAnimation() : m_FrameWidth(0), 
                           m_FrameHeight(0), 
                           m_TextureId(0),
                           m_Fps(0.0f) {
}
cAnimation::~cAnimation() {
}

void cAnimation::AddFrameGroup(std::string name, 
                               uint32_t startFrm, uint32_t endFrm) {
    auto iter = m_FrameGroups.find(name);
    if (iter != m_FrameGroups.end()) {
        S_LogError("cAnimation", 
                   "Framegroup with name '%s' already exists!", name.c_str());
        return;
    }

    m_FrameGroups[name] = sFramesGroup(startFrm, endFrm);
}
void cAnimation::RemoveFrameGroup(std::string name) {
    auto iter = m_FrameGroups.find(name);
    if (iter == m_FrameGroups.end()) {
        S_LogError("cAnimation", 
        "Frame group with name '%s' dose not exists, and can not be deleted",
        name.c_str());
        return;
    }

    m_FrameGroups.erase(iter);
}

void cAnimation::Init(int framesX /* = 0 */, int framesY /* = 0 */) {
    if (m_TextureId == 0) {
        S_LogError("cAnimation",
                   "Couldn't init animation. Texture not specified");
        return;
    }
    uint32_t txtW = S_GetTextureWidth(m_TextureId);
    uint32_t txtH = S_GetTextureHeight(m_TextureId);
    if (m_FrameWidth == 0 || m_FrameHeight == 0) {
        // Calculate frame size
        if (framesX == 0 && framesY == 0) {
            S_LogError("cAnimation", 
                       "Couldn't init animation. Frame number not specified");
            return;
        }

        m_FrameWidth = (int)(txtW / framesX);
        m_FrameHeight = (int)(txtH / framesY);
    } else {
        framesX = (int)(txtW / m_FrameWidth);
        framesY = (int)(txtH / m_FrameHeight);
    }

    for (int i = 0; i < framesX; i++) {
        for(int j = 0; j < framesY; j++) {
            sRect tmpSection;
            tmpSection.x = i * m_FrameWidth;
            tmpSection.y = j * m_FrameHeight;
            tmpSection.w = m_FrameWidth;
            tmpSection.h = m_FrameHeight;
            m_Frames.push_back(S_CreateSection(m_TextureId, tmpSection));
        }
    }
}
void cAnimation::Save(const std::string &filename) {
    // TODO:...
}
bool cAnimation::Load(const std::string &filename) {
    return false;    
}
void cAnimation::Unload() {
    for (auto &iter : m_Frames) {
        S_RemoveSection(iter);
    }
}

uint32_t cAnimation::CreateAnimator() {
    uint32_t newId = 1;
    
    if (m_Animators.size() > 0) {
        auto iter = m_Animators.end();
        --iter;
        newId = iter->first + 1;
    }

    m_Animators[newId] = sAnimator(0, m_Frames.size(), m_Fps);
    return newId;
}
void cAnimation::RemoveAnimatior(uint32_t animatorId) {
    auto iter = m_Animators.find(animatorId);
    if (iter == m_Animators.end()) {
        return;
    }
    m_Animators.erase(iter);
}
sAnimator *cAnimation::GetAnimator(uint32_t animatorId) {
    auto iter = m_Animators.find(animatorId);
    if (iter == m_Animators.end()) {
        return nullptr;
    }
    return &iter->second;
}

void cAnimation::Draw(uint32_t &animatorId, int &x, int &y) {
    sAnimator *animator = GetAnimator(animatorId);
    if (animator == nullptr) {
        S_LogError("cAnimation", 
                   "Non existing animator trying to draw. id: %d", animatorId);
        return;
    }
    S_DrawSection(m_Frames[animator->m_CurFrame], x, y);
}

void cAnimation::Tick() {
    for (auto &iter : m_Animators) {
        if (iter.second.m_IsAnimated) {
            TickAnimator(iter.second);
        }
    }
}

void cAnimation::TickAnimator(sAnimator &anim) { 
    if (STORM_TIME - anim.m_LastTick > (1000.0f / anim.m_CurFps)) {
        anim.m_CurFrame ++;
        
        if (anim.m_CurFrame >= anim.m_EndFrame) {
            anim.m_CurFrame = anim.m_StartFrame;
        }

        anim.m_LastTick = STORM_TIME;
    }
}

} /* namespace StormFramework */