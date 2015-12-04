#include "cBitmapFontManager.h"
#include "graphicsMain.h"

namespace StormFramework {

using namespace tinyxml2;

cBitmapFontManager::~cBitmapFontManager() {
    for (auto &iter : m_Fonts) {
        S_DestroyGraphics(iter.second.m_GraphicsId);
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
    // Loads font name
    XMLElement *element = doc.FirstChildElement("font");
    const char *fontName = element->Attribute("name");
    if (fontName == nullptr) {
        S_LogError("cBitmapFontManager",
                   "Invalid XML file. Could not find 'name' Attribute");
        return false;
    }
    // Loads font size 
    XMLElement *page = element->FirstChildElement("info");
    const char *tmpFontSize = page->Attribute("size");
    if (tmpFontSize == nullptr) {
        S_LogError("cBitmapFontManager", 
                   "Invalid XML file. Cold not find 'size' attribute");
        return false;
    }
    int fontSize = atoi(tmpFontSize);
    // Loads padding
    const char *tmpPadding = page->Attribute("padding");
    if (tmpPadding == nullptr) {
        S_LogError("cBitmapFontManager",
                   "Invalid XML file. Could not find 'padding' attribute");
        return false;
    }
    uint32_t pUp, pRight, pDown, pLeft;
    sscanf(tmpPadding, "%d,%d,%d,%d", &pUp, &pRight, &pDown, &pLeft);
    // Loads new line height
    page = element->FirstChildElement("common");
    const char *tmpLineH = page->Attribute("lineHeight");
    if (tmpLineH == nullptr) {
        S_LogError("cBitmapFontManager", 
                   "Invalid XML file. Could not find 'lineHeight' attribute");
        return false;
    }
    int lineHeight = atoi(tmpLineH);
    // Loads font texture
    page = element->FirstChildElement("pages")
                  ->FirstChildElement("page");

    const char *textureName = page->Attribute("file");
    if (textureName == nullptr) {
        S_LogError("cBitmapFontManager",
                   "Invalid XML file. Could not find 'texture' Attribute");
        return false;
    }

    uint32_t textureId = 0;
    uint32_t graphId = S_CreateGraphics(textureName, &textureId);
    if (textureId == 0) {
        S_LogError("cBitmapFontManager", "Texture loading error!");
        return false;
    }
    S_GraphModCenter(graphId, 0, 0);
    S_GraphModVisible(graphId, false);
    // Loads font characters
    element = element->FirstChildElement("chars");
    XMLElement *child = element->FirstChildElement("char");

    sBitmapFont tmpFont(textureId, graphId, fontSize, lineHeight);
    tmpFont.m_Padding[0] = pUp;
    tmpFont.m_Padding[1] = pRight;
    tmpFont.m_Padding[2] = pDown;
    tmpFont.m_Padding[3] = pLeft;
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
    S_DestroyGraphics(iter->second.m_GraphicsId);
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
    
    S_ModColorRaw(tmpFont.m_TextureId, r, g, b);
    for (int i = 0; i < (int)text.size(); i++) {
        auto iter = tmpFont.m_Characters.find(text[i]);
        if (iter == tmpFont.m_Characters.end()) {
            if (text[i] == '\n') {
                curY += tmpFont.m_LineHeight;
                curY += tmpFont.m_Padding[2]; // Padding bottom
                curX = x;
            }
            continue;
        }
        sBitmapChar &tmp = iter->second;
        tmpY = curY + tmp.yOffset;
        tmpY += tmpFont.m_Padding[0]; // Padding top

        curX += tmpFont.m_Padding[3]; // Padding left

        if (iter->first != ' ') {
            S_DrawRaw(tmpFont.m_TextureId, tmp.srcRect, curX, tmpY);
        }
        curX += tmp.advance + tmpFont.m_Padding[1]; // Padding right
        curX -= tmp.xOffset;
    }
}


} /* namespace StormFramework */
