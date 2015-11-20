/* 
 * File:   cEventBase.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:43 PM
 */

#ifndef CEVENTBASE_H__
#define CEVENTBASE_H__
#include <map>
#include <iostream>
#include "eStormKeys.h"
#include "../../defines.h"
#include "../framework/frameworkMain.h"

namespace StormFramework {


class cEventBase {
public:
    cEventBase() : m_MouseScroll(0), m_ToQuit(false), m_IsTextMode(false) {
        m_MouseKeys[0] = m_MouseKeys[1] = m_MouseKeys[2] = false;
    }
    virtual ~cEventBase() { }
    
    //While returns true, there is new event. If returns false, there is no anymore events
    virtual bool Update() { return false; }
    
    //Clears mouse scroll variable. Should be called after all event 
    //handler CB are called
    void Clear() { m_MouseScroll = 0; }
    
    //Return true if key is pressed
    bool IsKeyDown(StormKey key) { return m_Keys[key]; }
    //Return true if key is not pressed
    bool IsKeyUp(StormKey key) { return !m_Keys[key]; }
    //Return mouse coordinates
    sPoint &GetMouseLoc() { return m_MouseLoc; }
    //Return weather mouse button is down
    bool IsMouseLeft() { return m_MouseKeys[0]; }
    bool IsMouseRight() { return m_MouseKeys[1]; }
    bool IsMouseMiddle() { return m_MouseKeys[2]; }
    int GetMouseScroll() { return m_MouseScroll; }
    //Returns weather quit signal has been received
    bool IsQuit() { return m_ToQuit; }
    //Returns weather input handler is in text input mode
    bool IsTextInput() { return m_IsTextMode; }
    void StartTextInput() { m_IsTextMode = true; }
    void StopTextInput() { m_IsTextMode = false; }
    //Get text recorded from input
    std::string &GetText() { return m_InputText; }
    void SetText(const std::string &text) { m_InputText = text; }
protected:
    //Map of all keys <Key, isDown>
    std::map<int, bool> m_Keys;
    //Mouse coordinates
    sPoint m_MouseLoc;
    //True if mouse button is down
    bool m_MouseKeys[3];
    int m_MouseScroll;
    //True if quit signal has been received
    bool m_ToQuit;
    //True if text input mode is enabled
    bool m_IsTextMode;
    //This string contains text input form user
    std::string m_InputText;
};


}/* namespace StormFramework */
#endif  /* CEVENTBASE_H__ */

