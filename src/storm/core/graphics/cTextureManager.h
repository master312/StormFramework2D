/* 
 * File:   cTexturesManager.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:42 PM
 */

#ifndef CTEXTUREMANAGER_H__
#define CTEXTUREMANAGER_H__
#include <iostream>
#include <map>
#include "../framework/frameworkMain.h"
#include "../framework/cFileSystem.h"
#include "graphicsMain.h"
#include "cTextureBase.h"
#include "sTextureParametars.h"

namespace StormFramework {

struct sTextureSection {
    uint32_t m_TextureId;
    sRect m_Section;
};

class cTextureManager {
public:
    cTextureManager();
    ~cTextureManager();
    
    // Loads texture. Returns 0 on error
    uint32_t Load(const std::string &filename);
    // If texture is not in use, deletes it from memory
    // Return 1 if texture was deleted from memory, or -1 if usage number was decresed
    int Unload(uint32_t id);
    
    // Draw texture on screen
    void Draw(uint32_t &id, int &x, int &y);
    void Draw(uint32_t &id, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, int &x, int &y);
    void Draw(uint32_t &id, sRect &src, int &x, int &y, int &w, int &h);
    void Draw(uint32_t &id, sRect &src, sRect &dest);
    
    uint32_t CreateSection(uint32_t &textureId, sRect &section);
    void DrawSection(uint32_t &id, int &x, int &y);
    void DrawSection(uint32_t &id, int &x, int &y, int &w, int &h);
    void DrawSection(uint32_t &id, sRect &dest) { }
    void RemoveSection(uint32_t sectionId);

    void ModAngle(uint32_t &id, double &angle);
    void ModOpacity(uint32_t &id, uint8_t &opacity);

    cTextureBase *GetTexture(uint32_t &textureId);
    sTextureParametars *GetTextureParametars(uint32_t &textureId);

    // Returns memory usage of all loaded textures (in KB)
    uint32_t GetMemoryUsage() { return m_MemoryUsage; }
private:
    // Map of all loaded textures
    std::map<uint32_t, cTextureBase*> m_Textures;
    // Map of all texture parametars
    std::map<uint32_t, sTextureParametars> m_TextureParametars;
    // Map of texture ID's and their filenames. <FNAME, ID>
    std::map<std::string, uint32_t> m_TextureFilenames;
    // Map of all texture sections
    std::map<uint32_t, sTextureSection> m_Sections;
    // Memmory usage of all loaded textures (in KB))
    uint32_t m_MemoryUsage;
    
    
    // Returns pointer to new (empty) TextureObject created for active api
    cTextureBase *CreateTextureObject();
    // Create and load axual texture object.
    // Return pointer to loaded cTexture object. Or nullptr if there was and error
    cTextureBase *CreateAndLoad(const std::string &filename);
};

} /* namespace StormFramework */
#endif  /* CTEXTURESMANAGER_H */

