/* 
 * File:   cTexturesManager.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:42 PM
 */

#ifndef CTEXTUREMANAGER_H__
#define CTEXTUREMANAGER_H__
#include <iostream>
#include <sstream>
#include <map>
#include "../framework/frameworkMain.h"
#include "../framework/cFileSystem.h"
#include "graphicsMain.h"
#include "cTextureBase.h"
#include "sGraphicsObject.h"

namespace StormFramework {

class cTextureManager {
public:
    cTextureManager();
    ~cTextureManager();

    void Initialize();
    
    // Loads texture. Returns nulltpr on error
    cTextureBase *Load(const std::string &filename, uint32_t *id = nullptr);
    // Deletes @texture object from m_Textures.
    // THIS METHOD IS INTENDED TO BE USED ONLY BY CALLBACK
    // FROM cTextureBase CLASS!
    void Unload(cTextureBase *texture);
    // This method deletes all textures from memory
    // AND SHOULD NEVER BE CALLED IF PROGRAM IS STILL RUNNING
    // Used ONLY when 'quit' signal is received
    void UnloadAll();

    /*** Texture drawing methods ***/
    // Draws texture, using preset parameters
    void Draw(sGraphicsObject *par);
    // These methods should only be used for internal or debug purposes
    void Draw(uint32_t &id, int &x, int &y);
    void Draw(uint32_t &id, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, int &x, int &y);
    void Draw(uint32_t &id, sRect &src, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, sRect &dest);
    // // // // //

    void SetUseColorKeying(bool use) { m_UseColorKeying = use; }
    bool IsColorKeying() { return m_UseColorKeying; }
    void SetColorKey(sColor color) { m_ColorKey = color; }
    sColor &GetColorKey() { return m_ColorKey; }

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
    // Default color key values
    bool m_UseColorKeying;
    sColor m_ColorKey;
    
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

