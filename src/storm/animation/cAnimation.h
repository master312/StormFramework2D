/* 
 * File:   cAnimation.h
 * Author: master312
 *
 * Created on October 26, 2015, 8:02 PM
 * Princip sine miladine:
 *  -Every sAnimator object have sTextureObject, and theirs ids are the same
 *  -sTextureObject is texture section.
 *  -sTextureObject ~MUST~ be created and deleted trough cAnimation class
 *  -sAnimator contains pointer to sTextureObject (to make process easier on CPU)
 *  -sAnimator ~MUST~ be deleted before sTextureObject  
 */

#ifndef CANIMATION_H__
#define CANIMATION_H__
#define S_ANIMCHECKMACRO(x) sAnimator *a=GetAnimator(x); if (a==nullptr) return
#include <iostream>
#include <vector>
#include <map>
#include "../core/framework/frameworkMain.h"
#include "../core/graphics/graphicsMain.h"
#include "sAnimator.h"

namespace StormFramework {

class cAnimation {
public:
    cAnimation();
    void Clear();

    /* Fill this animation object with animation data 
     * returns < 0 on error */
    int Create(const std::string &texture, int w, int h, int x = 0, int y = 0);

    /* Logic tick */
    void Tick(uint32_t &delta);
    
    /* Creates new animator and returns it's id 
     * Animator ID is same as texture object ID */
    uint32_t CreateAnimator();
    void RemoveAnimator(uint32_t id);
    uint32_t CountAnimators() { return m_Animators.size(); }

    /* Adds new frame group to this animation. Returns < 0 on error */
    int AddGroup(const std::string &name, uint32_t start, uint32_t end);
    void RemoveGroup(const std::string &name);

    /* Setters and getters for default parameters */
    void SetFrame(sRect &frame) { m_Frame = frame; }
    sRect &GetFrame() { return m_Frame; }
    void SetFps(uint32_t &fps) { m_Fps = fps; }
    uint32_t &GetFps() { return m_Fps; }
    void SetStartFrame(uint32_t &start) { m_StartFrame = start; }
    uint32_t &GetStartFrame() { return m_StartFrame; }
    void SetEndFrame(uint32_t &end) { m_EndFrame = end; }
    uint32_t &GetEndFrame() { return m_EndFrame; }
    
    /* Setters and getters for animators */
    void AnimSetFrame(uint32_t &id, uint32_t &frame) { // Skips to @frame
        S_ANIMCHECKMACRO(id);
        a->m_CurFrame = frame;
    }
    uint32_t AnimGetFrame(uint32_t &id) {
        S_ANIMCHECKMACRO(id) 0;
        return a->m_CurFrame;
    }
    void AnimSetStart(uint32_t &id, uint32_t &start) {
        S_ANIMCHECKMACRO(id);
        a->m_StartFrame = start;
    }
    uint32_t AnimGetStart(uint32_t &id) {
        S_ANIMCHECKMACRO(id) 0;
        return a->m_StartFrame;
    }
    void AnimSetEnd(uint32_t &id, uint32_t &end) {
        S_ANIMCHECKMACRO(id);
        a->m_EndFrame = end;
    }
    uint32_t AnimGetEnd(uint32_t &id) {
        S_ANIMCHECKMACRO(id) 0;
        return a->m_EndFrame;
    }
    void AnimSetFps(uint32_t &id, uint32_t &fps) {
        S_ANIMCHECKMACRO(id);
        a->m_FrameTime = (float) 1000 / fps;
    }
    uint32_t AnimGetFps(uint32_t &id) {
        S_ANIMCHECKMACRO(id) 0;
        return (uint32_t) 1000 / a->m_FrameTime;
    }
    void AnimSetAnimated(uint32_t &id, bool animated) {
        S_ANIMCHECKMACRO(id);
        a->m_IsAnimated = animated;
    }
    bool AnimGetAnimated(uint32_t &id) {
        S_ANIMCHECKMACRO(id) false;
        return a->m_IsAnimated;
    }
private:
    /* Map of all animators 
     * <id, object> ID is same as sGraphicsObject ID in graphics manager */
    std::map<uint32_t, sAnimator> m_Animators;
    /* Map of all frame groups */
    std::map<std::string, sFramesGroup> m_Groups;
    
    /* Size of one frame, and start position on texture */
    sRect m_Frame;
    /* Default animation variables */
    uint32_t m_TextureId, m_Fps;
    uint32_t m_StartFrame, m_EndFrame;


    /* Returns pointer to animator with @id, or nullptr if not found */
    sAnimator *GetAnimator(uint32_t &id) {
        auto iter = m_Animators.find(id);
        if (iter == m_Animators.end()) {
            S_LogError("cAnimation", 
                       "Animator with ID %d dose not exists!", id);
            return nullptr;
        }
        return &iter->second;
    }
    /* Handle's animator ticking */
    void TickAnimator(sAnimator *anim);
};

} /* namespace StormFramework { */
#endif /* CANIMATION_H__ */