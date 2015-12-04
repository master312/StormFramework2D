/* 
 * File:   cAnimation.h
 * Author: master312
 *
 * Created on October 26, 2015, 8:02 PM
 * Princip sine miladine:
 *  -Every sAnimator object have sGraphicsObject, and theirs ids are the same
 *  -sGraphicsObject is texture section.
 *  -sGraphicsObject ~MUST~ be created and deleted trough cAnimation class
 *  -sAnimator contains pointer to sGraphicsObject (to make process easier on CPU)
 *  -sAnimator ~MUST~ be deleted before sGraphicsObject  
 */

#ifndef CANIMATION_H__
#define CANIMATION_H__
#define S_ANIMCHECKMACRO(x) sAnimator *a=GetAnimator(x); if (a==nullptr) return
#include <iostream>
#include <vector>
#include <map>
#include "../core/framework/frameworkMain.h"
#include "../core/framework/cBinaryFile.h"
#include "../core/graphics/graphicsMain.h"
#include "sAnimator.h"

namespace StormFramework {

class cAnimation {
public:
    cAnimation();
    void Clear();

    /* These methods save/load animation from file. 
     * Return < 0 on error */
    int Save(const std::string &filename);
    int Load(const std::string &filename);

    /* Loads texture, and initialize animation 
     * Returns < 0 on error */
    int Set(const std::string &texture,  uint32_t fps,
            int w, int h, int x = 0, int y = 0);

    /* Initialize animation (splits texture into sections) */
    int Init();

    /* Logic tick */
    void Tick(uint32_t &delta);
    
    /* Creates new animator and returns it's id 
     * Animator ID is same as texture object ID */
    uint32_t CreateAnimator();
    void RemoveAnimator(uint32_t &id);
    uint32_t CountAnimators() { return m_Animators.size(); }

    /* Adds new frame group to this animation. Returns < 0 on error */
    int AddGroup(const std::string &name, uint32_t start, uint32_t end);
    void RemoveGroup(const std::string &name);

    /* Called by interrupt manger to delete this texture
     * if its not longer in use. Should never be called manually */
    int DeletionInterrupt();

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
    std::string &GetFilename() { return m_Filename; }
private:
    /* Filename of this animation */
    std::string m_Filename;
    /* File name of texture */
    std::string m_TxtFilename;

    /* Default animation variables */
    uint32_t m_TextureId, m_Fps;
    uint32_t m_StartFrame, m_EndFrame;
    /* Size of one frame, and start position on texture */
    sRect m_Frame;
    
    /* Map of all frame groups */
    std::map<std::string, sFramesGroup> m_Groups;
    /* Map of all animators */
    std::map<uint32_t, sAnimator> m_Animators;
    /* Vector of coordinates of every frame in this animation */
    std::vector<sRect> m_Frames;
    
    /* This is set to true if animation object is ready to use */
    bool isInited;

    /* Handle's animator ticking */
    void TickAnimator(sAnimator *anim, uint32_t &delta);
};

} /* namespace StormFramework { */
#endif /* CANIMATION_H__ */