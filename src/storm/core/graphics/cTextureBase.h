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
    cTextureBase() : m_Filename(""), m_Usage(0),
                     m_MemoryUsage(0), m_DeleteCbId(0) { }
    virtual ~cTextureBase() { Unload(); }
    
    // Return > 0 on success, or -1 on error
    // keyR,G,B are transparency color keys.
    virtual int Load(sColor *colorKey = nullptr) { return 0; }
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
                      const double &angle, const int &opacity,
                      sPoint &center) { }
    
    virtual uint32_t GetPxWidth() = 0;
    virtual uint32_t GetPxHeight() = 0;    

    virtual void ModColor(uint8_t &r, uint8_t &g, uint8_t &b) { }

    void SetFilename(const std::string &filename) { m_Filename = filename; }
    std::string &GetFilename() { return m_Filename; }
    
    void IncUsage();
    void DecUsage();
    void SetUsage(uint32_t usage) { m_Usage = usage; }
    uint32_t &GetUsage() { return m_Usage; }
    // Returns true if texture is in use, or false if its not
    bool IsInUse() { return m_Usage != 0; }
    uint32_t &GetMemoryUsage() { return m_MemoryUsage; }

    // This method is called by callback handler
    // to delete texture, when m_Usage reaches zero
    // Should never be called manually
    int DeleteCb();
protected:
    std::string m_Filename;
    // Number of objects using this texture
    uint32_t m_Usage;
    // Size of this texture in memory, in bytes
    uint32_t m_MemoryUsage;
    // Holds ID of texture deletion callback.
    // If equals to zero, texture deletion 
    // progress is not started at the moment
    uint32_t m_DeleteCbId;
};

} /* namespace StormFramework */
#endif  /* CTEXTURE_H */

