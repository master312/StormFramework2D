/* 
 * File:   cEventManager.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:44 PM
 */

#ifndef CEVENTSMANAGER_H__
#define CEVENTSMANAGER_H__
#include <functional>
#include <map>
#include "cEventBase.h"
#include "../../defines.h"
#include "../framework/frameworkMain.h"
#include "../../callback/sCallback.h"

namespace StormFramework {
    
class cEventManager {
public:
    cEventManager();
    cEventManager(int api);
    ~cEventManager();
    
    void SetApi(int api);

    //callback function for handling events; 1 = low pririty, 0 - High p.
    void AddHandler(STypeCallback callback, 
                    const std::string &name, int priority = 1);
    void RemoveHandler(const std::string &name);
    
    //Clear all event handlers.
    //If @clearHigh is true, all high priority callbacks will also be cleared
    void ClearAll(bool clearHigh = false);
    
    void Tick();
    
    //If callback function calls this, every CB function after that one
    //won't be called
    void Eat();
    
    //This will return TRUE if Quit event has been received
    bool ToQuit() { return m_Input->IsQuit(); }
    //Returns pointer to input manager
    cEventBase *GetInput() { return m_Input; }
    bool IsInited() { return m_Input != nullptr; }
private:
    cEventBase *m_Input;
    bool m_IsEated;
    // Map stores high priority callbacks
    std::map<std::string, STypeCallback> m_CallbacksHigh;
    // Map stores low priority callbacks
    std::map<std::string, STypeCallback> m_CallbacksLow;
};


} /* namespace StormFramework */
#endif  /* CEVENTSMANAGER_H */

