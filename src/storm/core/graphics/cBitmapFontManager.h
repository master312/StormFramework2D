/* 
 * File:   sBitmapFont.h
 * Author: master312
 *
 * Created on November 11, 2015, 4:34 PM
 */

#ifndef CBITMAPFONTMANAGER_H__
#define CBITMAPFONTMANAGER_H__
#include <iostream>
#include <map>
#include "sBitmapFont.h"
#include "../framework/frameworkMain.h"
#include "../framework/cFileSystem.h"
#include "../../defines.h"
#include "../../thirdparty/tinyxml2.h"


namespace StormFramework {

class cBitmapFontManager {
public:
    ~cBitmapFontManager();

    /* Loads font form .xml file. Returns true on success */
    bool LoadFont(const std::string &filename);
    /* Unlaods font */
    void UnloadFont(const std::string &name);
    /* Draws text on screen */
    void DrawText(const std::string &text, int &x, int &y,  
                  uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a,
                  const std::string &font);
private:
    /* Map of all fonts */
    /* <fontName, fontObject> */
    std::map<std::string, sBitmapFont> m_Fonts;
};

} /* namespace StormFramework */
#endif /* CBITMAPFONTMANAGER_H__ */