/* 
 * File:   cGraphicsManager.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:07 PM
 */

#ifndef CGRAPHICSMANAGER_H__
#define CGRAPHICSMANAGER_H__
#include "../../defines.h"
#include "cGraphicsBase.h"
#include "graphicsMain.h"

namespace StormFramework {

class cGraphicsManager {
public:
    cGraphicsManager();
    ~cGraphicsManager();

    /* Initialize graphics rendering systems 
     * Returns < 0 on error */
    int Initialize();
    /* Returns true, if graphics was drawn at this call */
    bool Tick();

    cGraphicsBase *GetGraphics() { return m_Graphics; }
private:
    int m_Api;
    cGraphicsBase *m_Graphics;

    /* Time when last frame was drawn */
    uint32_t m_LastFrameTime;
    /* Current FPS */
    uint32_t m_CurrentFps;
    /* FPS counter refresh interval */
    uint32_t m_FpsCountRefresh;
    /* Target FPS */
    uint32_t m_TargetFps;
};

} /* namespace StormFramework */
#endif /* CGRAPHICSMANAGER_H__ */