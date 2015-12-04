#include "cAnimation.h"
#include "../core/graphics/graphicsMain.h"
#include "../core/graphics/cTextureManager.h"
#include "../core/graphics/cGraphicsManager.h"
#include "../core/interrupts/interruptsMain.h"

#include "cAnimationManager.h"
#include "animationsMain.h"

namespace StormFramework {

cAnimation::cAnimation() : m_Filename(""), m_TxtFilename(""),
                           m_TextureId(0), m_Fps(0), 
                           m_StartFrame(0), m_EndFrame(0),
                           isInited(false) {
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
int cAnimation::Save(const std::string &filename) { 
    m_Filename = filename;
    std::string fullPath = (char*)STORM_DIR_ANIMATIONS + filename;
    cBinaryFile fOut(fullPath, true);
    
    if (!fOut.IsOpen()) {
        S_LogError("cAnimation", 
                   "Could not open file '%s' for save", fullPath.c_str());
        return -1;
    }

    fOut.WriteString(m_TxtFilename);
    fOut.WriteUint32(m_Fps);
    fOut.WriteUint32(m_StartFrame);
    fOut.WriteUint32(m_EndFrame);
    fOut.WriteSRect(m_Frame);
    // Save frame groups
    fOut.WriteUint32(m_Groups.size());
    for (auto &iter : m_Groups) {
        fOut.WriteString(iter.first);
        fOut.WriteUint32(iter.second.m_Start);
        fOut.WriteUint32(iter.second.m_End);
    }
    fOut.Close();

    S_LogDebug("cAnimation", "Animation '%s' saved", fullPath.c_str());
    return 1;
}
int cAnimation::Load(const std::string &filename) {
    if (isInited)
        return 0;

    m_Filename = filename;
    std::string fullPath = (char*)STORM_DIR_ANIMATIONS + filename;
    cBinaryFile fOut(fullPath);
    
    if (!fOut.IsOpen()) {
        S_LogError("cAnimation", 
                   "Could not open file '%s' for load", fullPath.c_str());
        return -1;
    }

    m_TxtFilename = fOut.ReadString();
    m_Fps = fOut.ReadUint32();
    m_StartFrame = fOut.ReadUint32();
    m_EndFrame = fOut.ReadUint32();
    m_Frame = fOut.ReadSRect();
    // Save frame groups
    uint32_t groups = fOut.ReadUint32();
    for (uint32_t i = 0; i < groups; i++) {
        std::string tmpStr = fOut.ReadString();
        sFramesGroup tmpGr;
        tmpGr.m_Start = fOut.ReadUint32();
        tmpGr.m_End = fOut.ReadUint32();
        m_Groups[tmpStr] = tmpGr;
    }
    fOut.Close();
    
    S_GetTextureManager().Load(m_TxtFilename, &m_TextureId);
    if (m_TextureId == 0) {
        S_LogError("cAnimation", "Texture error!");
        return -1;
    }

    Init();

    S_LogDebug("cAnimation", "Animation '%s' loaded", fullPath.c_str());
    return 1;
}
int cAnimation::Set(const std::string &texture, uint32_t fps, 
                      int w, int h, int x /* = 0 */, int y /* = 0 */) {
    m_TxtFilename = texture;
    S_GetTextureManager().Load(m_TxtFilename, &m_TextureId);
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
    if ((int)txt->GetPxWidth() <= m_Frame.x) {
        tmpFrame.x = 0;
        triggerWarning ++;
    }
    if ((int)txt->GetPxWidth() <= m_Frame.x + m_Frame.w) {
        tmpFrame.w = txt->GetPxWidth();
        triggerWarning ++;
    }
    if ((int)txt->GetPxHeight() <= m_Frame.y) {
        tmpFrame.y = 0;
        triggerWarning ++;
    }
    if ((int)txt->GetPxWidth() <= m_Frame.y + m_Frame.h) {
        tmpFrame.x = txt->GetPxWidth();
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
    int framesX = (txt->GetPxWidth() - m_Frame.x) / m_Frame.w;
    int framesY = (txt->GetPxHeight() - m_Frame.y) / m_Frame.h;

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
            if (tmpRect.x + tmpRect.w > (int)txt->GetPxWidth()) {
                tmpRect.w = (tmpRect.x + tmpRect.w) - txt->GetPxWidth();
            }
            m_Frames.push_back(tmpRect);
        }
    }
    isInited = true;
    return 1;
}

void cAnimation::Tick(uint32_t &delta) {
    for (auto &iter : m_Animators) {
        if (iter.second.m_IsAnimated) {
            TickAnimator(&iter.second, delta);
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

    sGraphicsObject *tmp = S_GetGraphicsManager().GetLastCreated();
    tmp->m_IsAnimation = true;
    
    tmp->m_DestRect.w = m_Frame.w;
    tmp->m_DestRect.h = m_Frame.h;

    tmpAnimator.m_Object = tmp;
    m_Animators[tmpId] = tmpAnimator;

    return tmpId;
}
void cAnimation::RemoveAnimator(uint32_t &id) {
    auto iter = m_Animators.find(id);
    if (iter == m_Animators.end()) {
        return;
    }
    m_Animators.erase(iter);
    
    // S_DestroyGraphics(id);   This is not needed anymore...
    // because RemoveAnimator is now called from S_DestroyGraphics
    
    if (m_Animators.size() == 0) {
        S_AddDelayedCB(new STORM_INTERRUPT(STORM_ANIMATION_TIMEOUT, 
                              cAnimation, DeletionInterrupt, this));
    }
}

int cAnimation::AddGroup(const std::string &name, uint32_t start, uint32_t nd) {
    std::cout << "TODO: ADD GROUP" << std::endl;
    return 1;
}
void cAnimation::RemoveGroup(const std::string &name) {
    std::cout << "TODO: REMOVE GROUP" << std::endl;
}
int cAnimation::DeletionInterrupt() {
    if (m_Animators.size() > 0) {
        return 1;
    }
    S_GetAnimationManager().DeleteObject(this);
    return 1;
}
// Private methods
void cAnimation::TickAnimator(sAnimator *anim, uint32_t &delta) {
    if (!S_GetGraphicsManager().IsOnScreen(anim->m_Object)) {
        // This animator is out of screen
        return;
    }
    // Check if animation is ready to tick
    float framesLate = (STORM_TIME - anim->m_LastTime) / anim->m_FrameTime;
    if (framesLate >= 1.0f) {
        if (framesLate >= 2) {
            anim->m_CurFrame += (int)framesLate;
            if (anim->m_CurFrame >= anim->m_EndFrame) {
                uint32_t tmp = anim->m_CurFrame / anim->m_EndFrame;
                anim->m_CurFrame = (anim->m_EndFrame * tmp);
            }
        } else {
            anim->m_CurFrame ++;
        }
        
        if (anim->m_CurFrame >= anim->m_EndFrame) {
            anim->m_CurFrame = anim->m_StartFrame;
        }

        anim->m_Object->m_SrcRect = m_Frames[anim->m_CurFrame];        
        anim->m_LastTime = STORM_TIME;
    }
}

} /* namespace StormFramework */