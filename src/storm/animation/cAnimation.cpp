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
        m_Frames.clear();
        
        S_GetTextureManager().GetTexture(m_TextureId)->DecUsage();
    }
}

int cAnimation::Set(const std::string &texture, uint32_t fps, 
                      int w, int h, int x /* = 0 */, int y /* = 0 */) {
    S_GetTextureManager().Load(texture, &m_TextureId);
    if (m_TextureId == 0) {
        S_LogError("cAnimation", "Texture error!");
        return -1;
    }
    m_Fps = fps;
    m_Frame.x = x;
    m_Frame.y = y;
    m_Frame.w = w;
    m_Frame.h = h;
    return 1;
}

int cAnimation::Init() {
    cTextureBase *txt = S_GetTextureManager().GetTexture(m_TextureId);
    if (txt == nullptr) {
        S_LogError("cAnimation", 
                   "Init method called, but texture was not loaded");
        return -1;
    }
    sRect tmpFrame = m_Frame;
    int triggerWarning = 0;
    if ((int)txt->GetWidthPx() <= m_Frame.x) {
        tmpFrame.x = 0;
        triggerWarning ++;
    }
    if ((int)txt->GetWidthPx() <= m_Frame.x + m_Frame.w) {
        tmpFrame.w = txt->GetWidthPx();
        triggerWarning ++;
    }
    if ((int)txt->GetHeightPx() <= m_Frame.y) {
        tmpFrame.y = 0;
        triggerWarning ++;
    }
    if ((int)txt->GetWidthPx() <= m_Frame.y + m_Frame.h) {
        tmpFrame.x = txt->GetWidthPx();
        triggerWarning ++;
    }
    m_Frame = tmpFrame;
    if (triggerWarning > 0) {
        S_LogWarning("cAnimation", "Frame size is bigger then texture");
        if (triggerWarning == 4) {
            // TODO: Create one section here
            return 2;
        }
    }
    int framesX = (txt->GetWidthPx() - m_Frame.x) / m_Frame.w;
    int framesY = (txt->GetHeightPx() - m_Frame.y) / m_Frame.h;

    if (framesX > (int)m_StartFrame) { 
        m_StartFrame = 0; 
    }
    if ((framesX * framesY) > (int)m_EndFrame || m_EndFrame == 0) { 
        m_EndFrame = framesX * framesY; 
    }

    sRect tmpRect = tmpFrame;
    for (int j = 0; j < framesX; j++) {
        for (int i = 0; i < framesY; i++) {
            tmpRect.x = i * m_Frame.w;
            tmpRect.y = j * m_Frame.h;
            if (tmpRect.x + tmpRect.w > (int)txt->GetWidthPx()) {
                tmpRect.w = (tmpRect.x + tmpRect.w) - txt->GetWidthPx();
            }
            m_Frames.push_back(tmpRect);
        }
    }
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

    sTextureObject *tmp = S_GetGraphicsManager().GetLastCreated();
    
    tmp->m_DestRect.w = m_Frame.w;
    tmp->m_DestRect.h = m_Frame.h;

    tmpAnimator.m_Object = tmp;
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
    // TODO: Ove setuj SRC frame lokacije
    if (STORM_TIME - anim->m_LastTime >= anim->m_FrameTime) {
        if (anim->m_CurFrame >= anim->m_EndFrame) {
            anim->m_CurFrame = anim->m_StartFrame;
        }

        anim->m_Object->m_SrcRect = m_Frames[anim->m_CurFrame];
        
        anim->m_LastTime = STORM_TIME;
        anim->m_CurFrame ++;
    }
}

} /* namespace StormFramework */