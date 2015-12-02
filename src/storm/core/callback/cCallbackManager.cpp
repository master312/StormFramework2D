#include "cCallbackManager.h"
#include "sCallback.h"

namespace StormFramework {

cCallbackManager::~cCallbackManager() {
    Clear();
}
void cCallbackManager::Clear() {
    for (auto &iter : m_IntervalCallbacks) {
        delete iter.second;
    }
    m_IntervalCallbacks.clear();
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        delete m_DelayedCallbacks[i];
    }
    m_DelayedCallbacks.clear();
}

void cCallbackManager::Tick() {
    for (auto &iter : m_IntervalCallbacks) {
        if (iter.second->IsReady()) {
            iter.second->Call();
        }
    }
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        sCallback *tmpCb = m_DelayedCallbacks[i];
        if (tmpCb->IsReady()) {
            tmpCb->Call();
            m_DelayedCallbacks.erase(m_DelayedCallbacks.begin() + i);
            i = (i == 0) ? 0 : i - 1;
        }
    }
}

void cCallbackManager::AddIntervalCallback(const std::string &name,
                                           sCallback *callback) {
    if (IfExists(name)) {
        S_LogError("cCallbackManager", 
                   "Callback with name '%s' already exists", name.c_str());
        return;
    }
    m_IntervalCallbacks[name] = callback;
}
uint32_t cCallbackManager::AddDelayedCallback(sCallback *callback) {
    if (m_LastDelayedId == callback->m_LastTime) {
        S_LogWarning("cCallbackManager", 
                     "Multiple callbacks added in less the one MS.");
    }

    m_LastDelayedId = callback->m_LastTime;
    m_DelayedCallbacks.push_back(callback);
    return callback->m_LastTime;
}

void cCallbackManager::Remove(const std::string &name) {
    if (m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end()) {
        // Callback is "on interval" type
        delete m_IntervalCallbacks[name];
        m_IntervalCallbacks.erase(name);
    }
}
void cCallbackManager::Remove(uint32_t &id) {
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        if (m_DelayedCallbacks[i]->m_LastTime == id) {
            m_DelayedCallbacks.erase(m_DelayedCallbacks.begin() + i);
            return;
        }
    }
}
// Private methods
bool cCallbackManager::IfExists(const std::string &name) {
    return m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end();
}

} /* namespace StormFramework */