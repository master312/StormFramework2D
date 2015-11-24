/* 
 * File:   cGraphicsManager.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:07 PM
 */

#ifndef CGRAPHICSMANAGER_H__
#define CGRAPHICSMANAGER_H__
#include <algorithm>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include "../../defines.h"
#include "cGraphicsBase.h"
#include "graphicsMain.h"
#include "sTextureObject.h"
#include "cBitmapFontManager.h"

namespace StormFramework {

class cGraphicsManager {
public:
    cGraphicsManager();
    ~cGraphicsManager();

    /* Initialize graphics rendering systems 
     * Returns < 0 on error */
    int Initialize();
    /* Returns true, if graphics was drawn at this call */
    bool Tick();

    /* Loads texture, and creates new texture object. */
    /* Returns Object ID. @*id should only be used for debugging/testing */
    uint32_t LoadTexture(const std::string &filename, uint32_t *id = nullptr);
    void UnloadTexture(uint32_t &id);
    sTextureObject *GetObject(uint32_t &id);

    /* Creates texture section. Returns ID */
    uint32_t CreateSection(const std::string &filename, sRect &section);

    /* Texture object parameter setters/getters */
    void TxtModVisible(uint32_t &id, bool &isVisible);
    void TxtModPos(uint32_t &id, sPoint &point);
    void TxtModPos(uint32_t &id, int &x, int &y);
    void TxtModZ(uint32_t &id, int &z);
    void TxtModAngle(uint32_t &id, double &angle);
    void TxtModOpacity(uint32_t &id, uint8_t &opacity);
    void TxtModCenter(uint32_t &id, sPoint &center);
    void TxtModCenter(uint32_t &id, int &x, int &y);

    cGraphicsBase *GetGraphics() { return m_Graphics; }
    uint32_t GetOnScreenCount() { return m_OnScreen.size(); }
    uint32_t GetObjectsCount() { return m_TextureObjects.size(); }
private:
    int m_Api;
    cGraphicsBase *m_Graphics;
    std::string m_DebugString;

    /* Vector of all texture objects that are currently on screen */
    std::vector<sTextureObject*> m_OnScreen;
    /* Map of all texture objects */
    std::map<uint32_t, sTextureObject> m_TextureObjects;

    /* Draw all texture objects on screen */
    void DrawAll();
    /* Created new texture object, insert it into map, and return id */
    uint32_t GenerateObject(cTextureBase *texture, sRect *section = nullptr);

};

} /* namespace StormFramework */
#endif /* CGRAPHICSMANAGER_H__ */