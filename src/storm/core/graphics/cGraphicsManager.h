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
#include <sstream>
#include "../../defines.h"
#include "cGraphicsBase.h"
#include "graphicsMain.h"
#include "sGraphicsObject.h"
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
    uint32_t CreateObject(const std::string &filename, uint32_t *id = nullptr);
    void DestroyObject(uint32_t &id);
    sGraphicsObject *GetObject(uint32_t &id);

    /* Creates texture section. Returns ID */
    uint32_t CreateSection(const std::string &filename, sRect &section);
    uint32_t CreateSection(uint32_t &id, sRect &section);

    /* Texture object parameter setters/getters */
    void TxtModVisible(uint32_t &id, bool &isVisible);
    void TxtModPos(uint32_t &id, sPoint &point);
    void TxtModPos(uint32_t &id, int &x, int &y);
    void TxtModZ(uint32_t &id, int &z);
    void TxtModAngle(uint32_t &id, double &angle);
    void TxtModOpacity(uint32_t &id, uint8_t &opacity);
    void TxtModCenter(uint32_t &id, sPoint &center);
    void TxtModCenter(uint32_t &id, int &x, int &y);
    /* Returns true if object is on the screen */
    bool IsOnScreen(sGraphicsObject *obj);

    cGraphicsBase *GetGraphics() { return m_Graphics; }
    uint32_t GetOnScreenCount() { return m_OnScreen.size(); }
    uint32_t GetObjectsCount() { return m_TextureObjects.size(); }
    sGraphicsObject *GetLastCreated() { return m_LastObject; }
private:
    int m_Api;
    cGraphicsBase *m_Graphics;
    std::string m_DebugString;

    /* Vector of all objects that are currently on screen */
    std::vector<sGraphicsObject*> m_OnScreen;
    /* Map of all objects */
    std::map<uint32_t, sGraphicsObject> m_TextureObjects;
    /* Stores pointer to last created object */
    sGraphicsObject *m_LastObject;

    /* Draw all graphics objects on screen */
    void DrawAll();
    /* Draw geometry object */
    void DrawGeometry(sGraphicsObject *obj);
    /* Created new graphics object, insert it into map, and return id */
    uint32_t GenerateObject(cTextureBase *texture, sRect *section = nullptr);

};

} /* namespace StormFramework */
#endif /* CGRAPHICSMANAGER_H__ */