#include "cEventManager.h"
#include "SDL2/cEventSDL2.h"

namespace StormFramework {

cEventManager::cEventManager() : m_IsEated(false) {
    m_Input = nullptr;
}
cEventManager::cEventManager(int api) : m_IsEated(false) {
    m_Input = nullptr;
    SetApi(api);
}
cEventManager::~cEventManager() {
    if (m_Input != nullptr)
        delete m_Input;
}
void cEventManager::SetApi(int api) {
    switch (api) {
        case STORM_API_SDL:
            S_LogError("cEventManager", "Api 'SDL' not supported");
            break;
        case STORM_API_SDL2:
            m_Input = new cEventSDL2(); 
            break;
        case STORM_API_GLES:
            S_LogError("cEventManager", "Api 'GLES' not supported");
            break;
    }
}

void cEventManager::AddHandler(S_Callback callback, 
                                const std::string &name, 
                                int priority /* = 1 */) {
    if (priority == 1) {
        if (m_CallbacksLow.find(name) != m_CallbacksLow.end()) {
            S_LogError("cEventManager", 
                       "Callback named '%s' already exists", name.c_str());
            return;
        }
        m_CallbacksLow[name] = callback;        
    } else if (priority == 0) {
        if (m_CallbacksHigh.find(name) != m_CallbacksHigh.end()) {
            S_LogError("cEventManager", 
                       "Callback named '%s' already exists", name.c_str());
            return;
        }
        m_CallbacksHigh[name] = callback;
    } else {
        S_LogError("cEventManager", "Invalid priority specified");
    }
}
void cEventManager::RemoveHandler(const std::string &name) {
    if (m_CallbacksLow.find(name) != m_CallbacksLow.end()) {
        m_CallbacksLow.erase(name);
        return;
    }
    if(m_CallbacksHigh.find(name) != m_CallbacksHigh.end()) {
        m_CallbacksHigh.erase(name);
        return;
    }
}
void cEventManager::ClearAll(bool clearHigh /* = false */) {
    m_CallbacksLow.clear();
    if (clearHigh) {
        m_CallbacksHigh.clear();
        S_LogDebug("cEventManager", 
                   "All high priority event handlers deleted");
    }
    S_LogDebug("cEventManager", "All event handlers deleted");
}
void cEventManager::Tick() {
    while (m_Input->Update()) {
        for (auto &it : m_CallbacksHigh) {
            it.second();
            if (m_IsEated) {
                //Event was eaten by current handler
                m_IsEated = false;
                break;
            }
        }
        for (auto &it : m_CallbacksLow) {
            it.second();
            if (m_IsEated) {
                //Event was eaten by current handler
                m_IsEated = false;
                break;
            }
        }
    }
}
void cEventManager::Eat() {
    m_IsEated = true;
}

} /* namespace StormFramework */