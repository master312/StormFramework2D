#include "../../../defines.h"
#ifdef STORM_BUILD_SDL2
#include "cEventSDL2.h"
#include "../cEventManager.h"
#include "../eventsMain.h"

namespace StormFramework {

void cEventSDL2::Update() {
    cEventManager &eManager = S_GetEventManager();
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
                    eManager.CBOnTextType();
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

                        eManager.CBOnTextType();
                    }
                    break;
                } else {
                    if (m_Event.key.repeat == 0 && m_Keys[tmpKey] != 'd') {
                        m_Keys[tmpKey] = 'd';
                        eManager.CBOnKeyDown((StormKey)tmpKey);
                    }
                }
                break; }
            case SDL_KEYUP:
                if (m_Keys.count(m_Event.key.keysym.sym) != 0) {
                    m_Keys.erase(m_Keys.find(m_Event.key.keysym.sym));
                    eManager.CBOnKeyUp((StormKey)m_Event.key.keysym.sym);
                }
                break;
            case SDL_MOUSEMOTION:
                m_MouseLoc.x = m_Event.motion.x;
                m_MouseLoc.y = m_Event.motion.y;
                eManager.CBOnMouseMotion();
                break;
            case SDL_MOUSEBUTTONUP:
                if (m_Event.button.button == SDL_BUTTON_LEFT) {
                    if (m_MouseKeys[StormKey::MOUSE_LEFT] != false) {
                        m_MouseKeys[StormKey::MOUSE_LEFT] = false;
                        eManager.CBOnMouseUp(StormKey::MOUSE_LEFT);
                    }
                } else if (m_Event.button.button == SDL_BUTTON_RIGHT) {
                    if (m_MouseKeys[StormKey::MOUSE_RIGHT] != false) {
                        m_MouseKeys[StormKey::MOUSE_RIGHT] = false;
                        eManager.CBOnMouseUp(StormKey::MOUSE_RIGHT);
                    }
                } else if (m_Event.button.button == SDL_BUTTON_MIDDLE) {
                    if (m_MouseKeys[StormKey::MOUSE_MIDDLE] != false) {
                        m_MouseKeys[StormKey::MOUSE_MIDDLE] = false;
                        eManager.CBOnMouseUp(StormKey::MOUSE_MIDDLE);
                    }
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (m_Event.button.button == SDL_BUTTON_LEFT) {
                    if (m_MouseKeys[StormKey::MOUSE_LEFT] != true) {
                        m_MouseKeys[StormKey::MOUSE_LEFT] = true;
                        eManager.CBOnMouseDown(StormKey::MOUSE_LEFT);
                    }
                } else if (m_Event.button.button == SDL_BUTTON_RIGHT) {
                    if (m_MouseKeys[StormKey::MOUSE_RIGHT] != true) {
                        m_MouseKeys[StormKey::MOUSE_RIGHT] = true;
                        eManager.CBOnMouseDown(StormKey::MOUSE_RIGHT);
                    }
                } else if(m_Event.button.button == SDL_BUTTON_MIDDLE) {
                    if (m_MouseKeys[StormKey::MOUSE_MIDDLE] != true) {
                        m_MouseKeys[StormKey::MOUSE_MIDDLE] = true;
                        eManager.CBOnMouseDown(StormKey::MOUSE_MIDDLE);
                    }
                }
                break;
            case SDL_MOUSEWHEEL:
                m_MouseScroll = m_Event.wheel.y;
                eManager.CBOnMouseScroll(m_MouseScroll);
                break;
            default:
                break;
        }
    }
}

} /* namespace StormFramework */
#endif /* #ifdef STORM_BUILD_SDL2 */