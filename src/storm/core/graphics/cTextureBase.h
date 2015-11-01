/* 
 * File:   cTextureBase.h
 * Author: master312
 *
 * Created on September 27, 2015, 3:22 AM
 */

#ifndef CTEXTURE_H__
#define CTEXTURE_H__
#include <iostream>
#include "../framework/frameworkMain.h"

namespace StormFramework {

class cTextureBase {
public:
    cTextureBase() : m_Filename(""), m_Usage(0), m_MemoryUsage(0) { }
    virtual ~cTextureBase() { Unload(); }
    
    /* Return > 0 on success, or -1 on error */
    virtual int Load() { return 0; }
    virtual void Unload() { }
    bool Reload() {
        S_LogDebug("cTextureBase", "Reloading texture...");
        Unload();
        if (Load())
            return true;
        return false;
    }
    
    virtual void Draw(const int &srcX, const int &srcY, 
                      const int &srcW, const int &srcH,
                      const int &destX, const int &destY, 
                      const int &destW, const int &destH,
                      const int &angle, const int &opacity) { }
    
    virtual uint32_t GetWidthPx() = 0;
    virtual uint32_t GetHeightPx() = 0;
    
    void SetFilename(const std::string &filename) { m_Filename = filename; }
    std::string &GetFilename() { return m_Filename; }
    
    void IncUsage() { m_Usage++; }
    void DecUsage() { m_Usage--; }
    void SetUsage(uint32_t usage) { m_Usage = usage; }
    uint32_t &GetUsage() { return m_Usage; }
    // Returns true if texture is in use, or false if its not
    bool IsInUse() { return m_Usage != 0; }
    uint32_t &GetMemoryUsage() { return m_MemoryUsage; }
protected:
    std::string m_Filename;
    // Number of objects using this texture
    uint32_t m_Usage;
    // Size of this texture in memory, in bytes
    uint32_t m_MemoryUsage;
};

} /* namespace StormFramework */
#endif  /* CTEXTURE_H */

