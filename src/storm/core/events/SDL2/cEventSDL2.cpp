#include "cEventSDL2.h"

namespace StormFramework {

bool cEventSDL2::Update() {
    bool toReturn = true;
    while (SDL_PollEvent(&m_Event)) {
        switch (m_Event.type) {
            case SDL_WINDOWEVENT:
                /*
                switch (m_Event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        if (graphics != nullptr){
                            graphics->ResizeWindow(m_Event.window.data1, 
                                                   m_Event.window.data2);                        
                        }
                        break;
                }
                */
                break;
            case SDL_QUIT:
                m_ToQuit = true;
                break;
            case SDL_TEXTINPUT:
                if (m_IsTextMode) {
                    m_InputText += m_Event.text.text;
                } else {
                    toReturn = false;
                }
                break;
            case SDL_KEYDOWN: {
                SDL_Keycode tmpKey = m_Event.key.keysym.sym;
                if (m_IsTextMode) {
                    if (tmpKey == SDLK_LEFT || tmpKey == SDLK_RIGHT || tmpKey == SDLK_UP ||
                        tmpKey == SDLK_DOWN || (tmpKey >= SDLK_F1 && tmpKey <= SDLK_F15) || 
                        tmpKey == SDLK_ESCAPE || tmpKey == SDLK_BACKSPACE || 
                        tmpKey == SDLK_RSHIFT || tmpKey == SDLK_LSHIFT || tmpKey == SDLK_RCTRL ||
                        tmpKey == SDLK_LCTRL || tmpKey == SDLK_RALT || tmpKey == SDLK_LALT ||
                        tmpKey == KEY_RETURN || tmpKey == SDLK_KP_ENTER || tmpKey == SDLK_TAB) {

                        m_Keys[tmpKey] = 'd';

                        if (tmpKey == SDLK_BACKSPACE) {
                            if (m_InputText.size() > 0) {
                                m_InputText.erase(m_InputText.size() - 1);
                            }
                        }
                    }
                    break;
                } else {
                    if (m_Event.key.repeat != 0) {
                        toReturn = false;
                    } else {
                        if (m_Keys[tmpKey] == 'd') {
                            toReturn = false;
                        } else {
                            m_Keys[tmpKey] = 'd';
                        }
                    }
                }
                break; }
            case SDL_KEYUP:
                if (m_Keys.count(m_Event.key.keysym.sym) != 0) {
                    m_Keys.erase(m_Keys.find(m_Event.key.keysym.sym));
                }
                break;
            case SDL_MOUSEMOTION:
                m_MouseLoc.x = m_Event.motion.x;
                m_MouseLoc.y = m_Event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
                if (m_Event.button.button == SDL_BUTTON_LEFT) {
                    m_MouseKeys[StormKey::MOUSE_LEFT] = false;
                } else if (m_Event.button.button == SDL_BUTTON_RIGHT) {
                    m_MouseKeys[StormKey::MOUSE_RIGHT] = false;
                } else if (m_Event.button.button == SDL_BUTTON_MIDDLE) {
                    m_MouseKeys[StormKey::MOUSE_MIDDLE] = false;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (m_Event.button.button == SDL_BUTTON_LEFT) {
                    m_MouseKeys[StormKey::MOUSE_LEFT] = true;
                } else if (m_Event.button.button == SDL_BUTTON_RIGHT) {
                    m_MouseKeys[StormKey::MOUSE_RIGHT] = true;
                } else if(m_Event.button.button == SDL_BUTTON_MIDDLE) {
                    m_MouseKeys[StormKey::MOUSE_MIDDLE] = true;
                }
                break;
            case SDL_MOUSEWHEEL:
                m_MouseScroll = m_Event.wheel.y;
                break;
            default:
                toReturn = false;
                break;
        }
        return toReturn;
    }
    return false;
}

} /* namespace StormFramework */