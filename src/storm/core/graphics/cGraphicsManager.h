/* 
 * File:   cGraphicsManager.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:07 PM
 */

#ifndef CGRAPHICSMANAGER_H__
#define CGRAPHICSMANAGER_H__
#include <sstream>
#include "../../defines.h"
#include "cGraphicsBase.h"
#include "graphicsMain.h"
#include "cBitmapFontManager.h"

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

    std::string m_DebugVersion;
};

} /* namespace StormFramework */
#endif /* CGRAPHICSMANAGER_H__ */