/* 
 * File:   cEventManager.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:44 PM
 * This class handles all events, and call proper methods in cMain
 */

#ifndef CEVENTSMANAGER_H__
#define CEVENTSMANAGER_H__
#include <functional>
#include <map>
#include "../../defines.h"
#include "../framework/frameworkMain.h"
#include "cEventBase.h"

namespace StormFramework {
    
class cEventManager {
public:
    cEventManager();
    cEventManager(int api);
    ~cEventManager();
    
    void SetApi(int api);
    
    void Tick();
        
    // This will return TRUE if Quit event has been received
    bool ToQuit() { return m_Input->IsQuit(); }
    // Returns pointer to input manager
    cEventBase *GetInput() { return m_Input; }
    bool IsInited() { return m_Input != nullptr; }

    // These methods are called-back from cEventBase class
    void CBOnKeyDown(StormKey key);
    void CBOnKeyUp(StormKey key);
    void CBOnTextType();
    void CBOnMouseDown(StormKey key);
    void CBOnMouseUp(StormKey key);
    void CBOnMouseScroll(int scroll);
    void CBOnMouseMotion();
    void CBOnWindowResize();
    void CBOnWindowStateChange(int state);
private:
    cEventBase *m_Input;
};


} /* namespace StormFramework */
#endif  /* CEVENTSMANAGER_H */

