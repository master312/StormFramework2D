/* 
 * File:   cAnimation.h
 * Author: master312
 *
 * Created on October 26, 2015, 8:02 PM
 * TODO: Unload texture in Unload(), if loaded from Load(...)
 */

#ifndef CANIMATION_H__
#define CANIMATION_H__
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
    ~cAnimation();

    /***** Methods below are used only when creating new animation *****/ 
    /* Test sprite sheet to be used as animation */
    void SetTexture(uint32_t textureId) { m_TextureId = textureId; }
    void SetFrameSize(uint32_t width, uint32_t height) {
        m_FrameWidth = width;
        m_FrameHeight = height;
    }
    void AddFrameGroup(std::string name, uint32_t startFrm, uint32_t endFrm);
    void RemoveFrameGroup(std::string name);
    /* Initialize animation. Texture will be divided */
    /* into equal frames of equal size, if no frame size is specified */
    /* @framesX and @framesY are number of frames on axes X and Y */
    void Init(int framesX = 0, int framesY = 0);
    /*****  ***** ***** ***** ***** ***** ***** ***** ***** *****  *****/

    void Save(const std::string &filename);
    bool Load(const std::string &filename);
    void Unload();

    uint32_t CreateAnimator();
    void RemoveAnimatior(uint32_t animatorId);
    sAnimator *GetAnimator(uint32_t animatorId);

    void Draw(uint32_t &animatorId, int &x, int &y);
    void Draw(uint32_t &animatorId, int &x, int &y, int &w, int &h) { }

    void Tick();

    void SetFps(float fps) { m_Fps = fps; }
    uint32_t &GetFrameWidth() { return m_FrameWidth; }
    uint32_t &GetFrameHeight() { return m_FrameHeight; }
private:
    /* Map of all animators */
    std::map<uint32_t, sAnimator> m_Animators;
    /* Vector all texture sections (frames) */
    std::vector<uint32_t> m_Frames;
    /* Map of frame groups */
    std::map<std::string, sFramesGroup> m_FrameGroups;

    uint32_t m_FrameWidth;
    uint32_t m_FrameHeight;
    uint32_t m_TextureId;

    /* Default FPS */
    float m_Fps;

    void TickAnimator(sAnimator &anim);
};

} /* namespace StormFramework { */
#endif /* CANIMATION_H__ */