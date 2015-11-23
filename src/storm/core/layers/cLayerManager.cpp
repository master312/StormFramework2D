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

    S_Callback tmpCb = std::bind(&cLayerManager::EventHandler, this);
    S_GetEventManager().AddHandler(tmpCb, "LayerManager", 0);
}
void cLayerManager::PushLayer(cLayerBase *state) {
    state->OnInit();
    state->SetState(STARTED);
    if (m_Layers.size() > 0) {
        m_Layers[m_ActiveLayer]->Pause();
    }
    m_Layers.push_back(state);
    UpdateActiveLayer();
}
void cLayerManager::Clear() {
    for (uint32_t i = 0; i < m_Layers.size(); i++) {
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
int cLayerManager::EventHandler() {
    if (!m_Layers[m_ActiveLayer]->IsStarted()) {
        UpdateActiveLayer();
        if (m_ActiveLayer == 0) {
            return 0;
        }
    }
    m_Layers[m_ActiveLayer]->OnEvent();
    return 0;
}

void cLayerManager::UpdateActiveLayer() {
    m_ActiveLayer = 0;
    for (int i = (int)m_Layers.size() - 1; i >= 0; i--) {
        if (m_Layers[i]->IsStarted() && m_ActiveLayer == 0) {
            m_ActiveLayer = i;
        } else if (m_Layers[i]->IsStoped()) {
            delete m_Layers[i];
            m_Layers.erase(m_Layers.begin() + i);
        }
    }
}

} /* namespace StormFramework */