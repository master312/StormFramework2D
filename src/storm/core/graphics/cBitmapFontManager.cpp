#include "cBitmapFontManager.h"
#include "graphicsMain.h"

namespace StormFramework {

using namespace tinyxml2;

cBitmapFontManager::~cBitmapFontManager() {
    for (auto &iter : m_Fonts) {
        S_UnloadTexture(iter.second.m_TextureId);
    }
    m_Fonts.clear();
}

bool cBitmapFontManager::LoadFont(const std::string &filename) {
    std::string fullPath = (char*)STORM_DIR_FONTS + filename;
    cFileSystem::ConvertPath(fullPath);

    XMLDocument doc;
    if (doc.LoadFile(fullPath.c_str()) != 0) {
        S_LogError("cBitmapFontManager", 
                   "Could not open file '%s'", fullPath.c_str());
        return false;
    }

    XMLElement *element = doc.FirstChildElement("font");
    const char *fontName = element->Attribute("name");
    if (fontName == nullptr) {
        S_LogError("cBitmapFontManager",
                   "Invalid XML file. Could not find 'name' Attribute");
        return false;
    }
    XMLElement *page = element->FirstChildElement("pages")
                              ->FirstChildElement("page");

    const char *textureName = page->Attribute("file");
    if (textureName == nullptr) {
        S_LogError("cBitmapFontManager",
                   "Invalid XML file. Could not find 'texture' Attribute");
        return false;
    }

    uint32_t textureId = S_LoadTexture(textureName);
    if (textureId == 0) {
        S_LogError("cBitmapFontManager", "Texture loading error!");
        return false;
    }

    element = element->FirstChildElement("chars");
    XMLElement *child = element->FirstChildElement("char");

    sBitmapFont tmpFont(textureId);
    for (; child; child = child->NextSiblingElement()) {
        char charId = (char)(atoi(child->Attribute("id")));
        
        sBitmapChar tmpChar;
        tmpChar.srcRect.x = atoi(child->Attribute("x"));
        tmpChar.srcRect.y = atoi(child->Attribute("y"));
        tmpChar.srcRect.w = atoi(child->Attribute("width"));
        tmpChar.srcRect.h = atoi(child->Attribute("height"));
        tmpChar.xOffset = atoi(child->Attribute("xoffset"));
        tmpChar.yOffset = atoi(child->Attribute("yoffset"));
        tmpChar.advance = atoi(child->Attribute("xadvance"));

        tmpFont.m_Characters[charId] = tmpChar;
    }


    m_Fonts[fontName] = tmpFont;
    S_LogInfo("cBitmapFontManager", "Font '%s' loaded", fontName);
    return true;
}
void cBitmapFontManager::UnloadFont(const std::string &name) {
    auto iter = m_Fonts.find(name);
    if (iter == m_Fonts.end()) {
        return;
    }
    S_UnloadTexture(iter->second.m_TextureId);
    m_Fonts.erase(iter);
}
void cBitmapFontManager::DrawText(const std::string &text, int &x, int &y,
                                  uint8_t &r, uint8_t &g, 
                                  uint8_t &b, uint8_t &a,
                                  const std::string &font) {
    auto iter = m_Fonts.find(font);
    if (iter == m_Fonts.end()) {
        S_LogError("cBitmapFontManager", 
                   "Could not find font '%s'", font.c_str());
        return;
    }

    sBitmapFont &tmpFont = iter->second;

    int curX = x;
    int curY = y;
    int tmpY = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        auto iter = tmpFont.m_Characters.find(text[i]);
        if (iter == tmpFont.m_Characters.end()) {
            continue;
        }
        sBitmapChar &tmp = iter->second;
        tmpY = curY + tmp.yOffset;

        if (iter->first != ' ') {
            S_TextureModColor(tmpFont.m_TextureId, r, g, b);
            S_RefDrawTexture(tmpFont.m_TextureId, tmp.srcRect, curX, tmpY);
        }
        curX += tmp.advance;
        curX -= tmp.xOffset;
    }
}


} /* namespace StormFramework */
