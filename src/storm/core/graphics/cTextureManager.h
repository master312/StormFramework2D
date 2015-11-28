/* 
 * File:   cTexturesManager.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:42 PM
 * TODO: int ClearTick(); is not needed!!!
 * Create new "Clear()" method in cTextureBase
 * and call if after delay (using calback system)
 * if texture usage drops to zero.
 */

#ifndef CTEXTUREMANAGER_H__
#define CTEXTUREMANAGER_H__
#include <iostream>
#include <sstream>
#include <map>
#include "../../callback/callbackMain.h"
#include "../framework/frameworkMain.h"
#include "../framework/cFileSystem.h"
#include "graphicsMain.h"
#include "cTextureBase.h"
#include "sTextureObject.h"

namespace StormFramework {

class cTextureManager {
public:
    cTextureManager();
    ~cTextureManager();

    void Initialize();
    
    // Loads texture. Returns nulltpr on error
    cTextureBase *Load(const std::string &filename, uint32_t *id = nullptr);
    // Delete all unused texture. 
    // Called by callback system on specified interval 
    int ClearTick();
    
    /*** Texture drawing methods ***/
    // Draws texture, using preset parameters
    void Draw(sTextureObject *par);
    // These methods should only be used for internal or debug purposes
    void Draw(uint32_t &id, int &x, int &y);
    void Draw(uint32_t &id, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, int &x, int &y);
    void Draw(uint32_t &id, sRect &src, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, sRect &dest);
    // // // // //

    cTextureBase *GetTexture(uint32_t &textureId);

    // Returns memory usage of all loaded textures (in KB)
    uint32_t GetMemoryUsage() { return m_MemoryUsage; }
    // Returns number of textures loaded
    uint32_t GetTextureCount() { return m_Textures.size(); }

    // Return debug string (count of objects)
    std::string &GetDebugString() { return m_DebugString; }
private:
    // Map of all loaded textures
    std::map<uint32_t, cTextureBase*> m_Textures;
    // Map of texture ID's and their filenames. <FNAME, ID>
    std::map<std::string, uint32_t> m_TextureFilenames;
    // Memory usage of all loaded textures (in KB))
    uint32_t m_MemoryUsage;
    // String containing debug info
    std::string m_DebugString;
    // Default texture center (0, 0)
    // This variable is created for optimization purposes only
    sPoint m_DefCenter;
    
    // Returns pointer to new (empty) TextureObject created for active api
    cTextureBase *CreateTextureObject();
    // Create and load axual texture object.
    // Return pointer to loaded cTexture object. Or nullptr if there was and error
    cTextureBase *CreateAndLoad(const std::string &filename);
    // Updates m_DebugString text
    void UpdateDebugString();

};

} /* namespace StormFramework */
#endif  /* CTEXTURESMANAGER_H */

