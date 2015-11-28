#include "cAnimation.h"
#include "../core/graphics/graphicsMain.h"
#include "../core/graphics/cTextureManager.h"
#include "../core/graphics/cGraphicsManager.h"

namespace StormFramework {

cAnimation::cAnimation() : m_TextureId(0), m_Fps(0),
                           m_StartFrame(0), m_EndFrame(0) {

}
void cAnimation::Clear() {
    if (m_TextureId > 0) {
        for (auto &iter : m_Animators) {
            S_DestroyGraphics(iter.first);
        }
        m_Animators.clear();
        S_GetTextureManager().GetTexture(m_TextureId)->DecUsage();
    }
}

int cAnimation::Create(const std::string &texture, 
                      int w, int h, int x /* = 0 */, int y /* = 0 */) {
    S_GetTextureManager().Load(texture, &m_TextureId);
    if (m_TextureId == 0) {
        S_LogError("cAnimation", "Texture error!");
        return -1;
    }
    m_Frame.x = x;
    m_Frame.y = y;
    m_Frame.w = w;
    m_Frame.h = h;
    return 1;
}

void cAnimation::Tick(uint32_t &delta) {
    for (auto &iter : m_Animators) {
        if (iter.second.m_IsAnimated) {
            TickAnimator(&iter.second);
        }
    }
}

uint32_t cAnimation::CreateAnimator() {
    sAnimator tmpAnimator(m_StartFrame, m_EndFrame, m_Fps);
    uint32_t tmpId = S_CreateSection(m_TextureId, m_Frame);
    
    if (tmpId == 0) {
        S_LogError("cAnimation", "Could not create new section!");
        return 0;
    }
    
    m_Animators[tmpId] = tmpAnimator;

    return tmpId;    
}
void cAnimation::RemoveAnimator(uint32_t id) {
     auto iter = m_Animators.find(id);
    if (iter == m_Animators.end()) {
        return;
    }
    m_Animators.erase(iter);
    S_DestroyGraphics(id);
}

int cAnimation::AddGroup(const std::string &name, uint32_t start, uint32_t nd) {
    std::cout << "TODO: ADD GROUP" << std::endl;
}
void cAnimation::RemoveGroup(const std::string &name) {
    std::cout << "TODO: REMOVE GROUP" << std::endl;
}
// Private methods
void cAnimation::TickAnimator(sAnimator *anim) {
    // Check if animation is ready to tick
    if (STORM_TIME - anim->m_LastTime >= anim->m_FrameTime) {
        anim->m_CurFrame ++;
        if (anim->m_CurFrame > anim->m_EndFrame) {
            anim->m_CurFrame = anim->m_StartFrame;
        }
        anim->m_LastTime = STORM_TIME;
    }
}

} /* namespace StormFramework */