#include "cGraphicsBase.h"

namespace StormFramework {

cGraphicsBase::cGraphicsBase() :
    m_Title("Storm framework"),
    m_Width(1024),
    m_Height(768),
    m_Fullscreen(false),
    m_MaxTextureW(0),
    m_MaxTextureH(0) {
    
}

void cGraphicsBase::Set(std::string _title /* = "Storm Framework" */, 
                    uint32_t _width /* = 1024 */, 
                    uint32_t _height /* = 768 */ ) {
    m_Title = _title;
    m_Width = _width;
    m_Height = _height;
    m_Fullscreen = false;
    m_MaxTextureW = 0;
    m_MaxTextureH = 0;
}


}