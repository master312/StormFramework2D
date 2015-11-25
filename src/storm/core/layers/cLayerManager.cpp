#include "cLayerManager.h"
#include "../events/eventsMain.h"
#include "../events/cEventManager.h"
#include <functional>

namespace StormFramework {

cLayerManager::cLayerManager() : m_ActiveLayer (0) {
}
cLayerManager::~cLayerManager() {
    Clear();
}
void cLayerManager::Init() {
    if (!S_GetEventManager().IsInited()) {
        S_LogError("cLayerManager",
                   "Must initialize event manager before state manager");
        return;
    }
    m_Layers.push_back(nullptr);
}
void cLayerManager::PushLayer(cLayerBase *state) {
    state->OnInit();
    state->SetState(STARTED);
    if (m_Layers.size() > 0 && m_ActiveLayer > 0) {
        m_Layers[m_ActiveLayer]->Pause();
    }
    m_Layers.push_back(state);
    UpdateActiveLayer();
}
void cLayerManager::Clear() {
    for (uint32_t i = 1; i < m_Layers.size(); i++) {
        m_Layers[i]->OnShutdown();
        delete m_Layers[i];
    }
    m_Layers.clear();
}
void cLayerManager::LogicTick(uint32_t &delta) {
    if (m_Layers.empty()) {
        S_LogError("cLayerManager", "No states found");
        return;
    }
    if (!m_Layers[m_ActiveLayer]->IsStarted()) {
        UpdateActiveLayer();
        if (m_ActiveLayer == 0) {
            return;
        }
    }
    m_Layers[m_ActiveLayer]->OnLogicTick(delta);
}
void cLayerManager::GraphicsTick() {
    if (m_Layers.empty()) {
        S_LogError("cLayerManager", "No states found");
        return;
    }
    if (!m_Layers[m_ActiveLayer]->IsStarted()) {
        UpdateActiveLayer();
        if (m_ActiveLayer == 0) {
            return;
        }
    }
    m_Layers[m_ActiveLayer]->OnGraphicsTick();
}
void cLayerManager::EventKeyDown(StormKey &key) {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnKeyDown(key);
}
void cLayerManager::EventKeyUp(StormKey &key) {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnKeyUp(key);
}
void cLayerManager::EventTextType() {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnTextType();
}
void cLayerManager::EventMouseDown(StormKey &key) {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnMouseDown(key);
}
void cLayerManager::EventMouseUp(StormKey &key) {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnMouseUp(key);
}
void cLayerManager::EventMouseScroll(int &scroll) {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnMouseScroll(scroll);
}
void cLayerManager::EventMouseMotion() {
    if (m_ActiveLayer == 0) { return; }
    m_Layers[m_ActiveLayer]->OnMouseMotion();
}   
void cLayerManager::EventWindowResize() {
    if (m_ActiveLayer == 0) { return; }

}
void cLayerManager::EventWindowStateChange(int &state) {
    if (m_ActiveLayer == 0) { return; }

}

void cLayerManager::UpdateActiveLayer() {
    m_ActiveLayer = 0;
    for (int i = (int)m_Layers.size() - 1; i >= 0; i--) {
        if (m_Layers[i] == nullptr) 
            continue;

        if (m_Layers[i]->IsStarted() && m_ActiveLayer == 0) {
            m_ActiveLayer = i;
        } else if (m_Layers[i]->IsStoped()) {
            delete m_Layers[i];
            m_Layers.erase(m_Layers.begin() + i);
        }
    }
}

} /* namespace StormFramework */