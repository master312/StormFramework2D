#include "cInterruptManager.h"
#include "sInterrupt.h"

namespace StormFramework {

cInterruptManager::~cInterruptManager() {
    Clear();
}
void cInterruptManager::Clear() {
    for (auto &iter : m_IntervalCallbacks) {
        delete iter.second;
    }
    m_IntervalCallbacks.clear();
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        delete m_DelayedCallbacks[i];
    }
    m_DelayedCallbacks.clear();
}

void cInterruptManager::Tick() {
    for (auto &iter : m_IntervalCallbacks) {
        if (iter.second->IsReady()) {
            iter.second->Call();
        }
    }
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        sInterrupt *tmpCb = m_DelayedCallbacks[i];
        if (tmpCb->IsReady()) {
            tmpCb->Call();
            delete m_DelayedCallbacks[i];
            m_DelayedCallbacks.erase(m_DelayedCallbacks.begin() + i);
            i = (i == 0) ? 0 : i - 1;
        }
    }
}

void cInterruptManager::AddInterrupt(const std::string &name,
                                           sInterrupt *callback) {
    if (IfExists(name)) {
        S_LogError("cInterruptManager", 
                   "Callback with name '%s' already exists", name.c_str());
        return;
    }
    m_IntervalCallbacks[name] = callback;
}
uint32_t cInterruptManager::AddDelayedCallback(sInterrupt *callback) {
    m_NextId++;
    callback->m_Id = m_NextId;
    m_DelayedCallbacks.push_back(callback);
    return m_NextId;
}

void cInterruptManager::Remove(const std::string &name) {
    if (m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end()) {
        // Callback is "on interval" type
        delete m_IntervalCallbacks[name];
        m_IntervalCallbacks.erase(name);
    }
}
void cInterruptManager::Remove(uint32_t &id) {
    for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
        if (m_DelayedCallbacks[i]->m_Id == id) {
            delete m_DelayedCallbacks[i];
            m_DelayedCallbacks.erase(m_DelayedCallbacks.begin() + i);
            return;
        }
    }
}
// Private methods
bool cInterruptManager::IfExists(const std::string &name) {
    return m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end();
}

} /* namespace StormFramework */