/* 
 * File:   sAnimator.h
 * Author: master312
 *
 * Created on October 26, 2015, 8:08 PM
 */

#ifndef CANIMATOR_H__
#define CANIMATOR_H__
#include "../core/framework/frameworkMain.h"
#include "../core/graphics/sTextureObject.h"

namespace StormFramework {

struct sAnimator {
    /* Frame that is currently being drawn */
    uint32_t m_CurFrame;
    /* How much time one frame last */
    float m_FrameTime;
    /* Start frame */
    uint32_t m_StartFrame;
    /* End frame */
    uint32_t m_EndFrame;
    /* Time of last frame change */
    uint32_t m_LastTime;
    /* Is animation running (auto ticking) */
    bool m_IsAnimated;

    sAnimator () : m_CurFrame(0),
                   m_FrameTime(0.0f),
                   m_StartFrame(0),
                   m_EndFrame(0),
                   m_LastTime(STORM_TIME),
                   m_IsAnimated(true) { }
    sAnimator (uint32_t start, uint32_t end, uint32_t fps) :
               m_CurFrame(start),
               m_StartFrame(start),
               m_EndFrame(end),
               m_LastTime(STORM_TIME),
               m_IsAnimated(true) { 

        m_FrameTime = (float) 1000 / fps;
    }
};


struct sFramesGroup {
    uint32_t m_Start;
    uint32_t m_End;

    sFramesGroup () : m_Start(0), m_End(0) { }
    sFramesGroup (uint32_t start, uint32_t end) 
                : m_Start(start), m_End(end) { } 
};


} /* namespace StormFramework { */
#endif /* CANIMATOR_H__ */