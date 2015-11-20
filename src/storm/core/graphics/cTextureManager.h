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
#include <vector>
#include <map>
#include "../framework/frameworkMain.h"
#include "../framework/cFileSystem.h"
#include "graphicsMain.h"
#include "cTextureBase.h"
#include "sTextureParameters.h"

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
    // Return 1 if texture was deleted from memory, 
    // 0 if usage number was decreased, or -1 on error  
    int Unload(uint32_t id);
    
    /*** Texture drawing methods ***/
    // This method draws all textures that are currently visible
    void DrawAll();
    // These methods override texture parameters
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

    /*** Texture parameter modifying methods ***/
    void ModVisible(uint32_t &id, bool &isVisible);
    void ModPos(uint32_t &id, sPoint &point);
    void ModPos(uint32_t &id, int &x, int &y);
    void ModAngle(uint32_t &id, double &angle);
    void ModOpacity(uint32_t &id, uint8_t &opacity);
    void ModCenter(uint32_t &id, sPoint &center);
    void ModCenter(uint32_t &id, int &x, int &y);

    cTextureBase *GetTexture(uint32_t &textureId);
    sTextureParameters *GetTextureParametars(uint32_t &textureId);

    // Returns memory usage of all loaded textures (in KB)
    uint32_t GetMemoryUsage() { return m_MemoryUsage; }
    // Returns number of textures loaded
    uint32_t GetTextureCount() { return m_Textures.size(); }
    // Returns number of texture instances
    uint32_t GetInstanceCount() { return m_TextureParameters.size(); }
    // Return number of sections
    uint32_t GetSectionCount() { return m_Sections.size(); }
    // Return debug string (count of objects)
    std::string &GetDebugString() { return m_DebugString; }
private:
    // Map of all loaded textures
    std::map<uint32_t, cTextureBase*> m_Textures;
    // Map of all texture parameters
    std::map<uint32_t, sTextureParameters> m_TextureParameters;
    // Map of texture ID's and their filenames. <FNAME, ID>
    std::map<std::string, uint32_t> m_TextureFilenames;
    // Vector of all textures that are currently on screen
    std::vector<uint32_t> m_OnScreen;   // TODO: Change this to map when "depth"(z) support come...
    // Map of all texture sections
    std::map<uint32_t, sTextureSection> m_Sections;
    // Memory usage of all loaded textures (in KB))
    uint32_t m_MemoryUsage;
    // String containing debug info
    std::string m_DebugString;
    
    
    // Returns pointer to new (empty) TextureObject created for active api
    cTextureBase *CreateTextureObject();
    // Create and load axual texture object.
    // Return pointer to loaded cTexture object. Or nullptr if there was and error
    cTextureBase *CreateAndLoad(const std::string &filename);
    // Creates new texture parameter and return it's id
    uint32_t CreateParameters(cTextureBase *texture);
    // Draws texture, using preset parameters
    void Draw(uint32_t &id);
    // Updates m_DebugString text
    void UpdateDebugString();

};

} /* namespace StormFramework */
#endif  /* CTEXTURESMANAGER_H */

