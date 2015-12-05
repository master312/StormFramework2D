/* 
 * File:   cGraphicsBase.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:04 PM
 */

#ifndef CGRAPHICSBASE_H__
#define CGRAPHICSBASE_H__
#include <iostream>
#include "../../defines.h"
#include "../framework/frameworkMain.h"
#include "../framework/sPrimitives.h"

namespace StormFramework {

class cGraphicsBase {
public:
    cGraphicsBase();
    virtual ~cGraphicsBase() { }
    
    void Set(std::string _title = "Storm Framework", 
             uint32_t _width = 1024, uint32_t _height = 768);
    virtual int Initialize() { return 0; }
    
    // Flips back buffer to screen
    virtual void SwapBuffers() { }
    virtual void ClearScreen() { }
    
    virtual void ResizeWindow(uint32_t w, uint32_t h) { }
    virtual void SetWindowType(int type) { }
    
    virtual void DrawFillRect(sRect &rect, sColor *color = nullptr) { }
    virtual void DrawRect(sRect &rect, sColor *color = nullptr) { }
    virtual void DrawFillCircle(int &x, int &y, 
                                uint32_t &radius,
                                sColor *color = nullptr) { }
    virtual void DrawCircle(int &x, int &y, 
                                uint32_t &radius,
                                uint32_t width = 1,
                                sColor *color = nullptr) { }

    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
    bool IsFullscreen() { return m_Fullscreen; }
    int GetMaxTxtWidth() { return m_MaxTextureW; }
    int GetMaxTxtHeight() { return m_MaxTextureH; }
protected:
    std::string m_Title;
    uint32_t m_Width, m_Height;
    bool m_Fullscreen;
    int m_MaxTextureW;
    int m_MaxTextureH;
    
    virtual void DrawPixel(float x, float y) { }
    virtual void DrawRect(float x, float y, float w, float h, bool isFill) { }
};

}

#endif  /* CGRAPHICS_H */