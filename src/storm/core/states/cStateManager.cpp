#include "cStateManager.h"

namespace StormFramework {

cStateManager::cStateManager() : m_ActiveState (0) {
}
cStateManager::~cStateManager() {
	Clear();
}
void cStateManager::PushState(cStateBase *state) {
	state->OnInit();
	state->SetState(STARTED);
	if (m_States.size() > 0) {
		m_States[m_ActiveState]->Pause();
	}
	m_States.push_back(state);
	UpdateActiveState();
}
void cStateManager::Clear() {
	for (uint32_t i = 0; i < m_States.size(); i++) {
		m_States[i]->OnShutdown();
		delete m_States[i];
	}
	m_States.clear();
}
void cStateManager::LogicTick(uint32_t &delta) {
	if (m_States.empty()) {
		S_LogError("cStateManager", "No states found");
		return;
	}
	if (!m_States[m_ActiveState]->IsStarted()) {
		UpdateActiveState();
		if (m_ActiveState == 0) {
			return;
		}
	}
	m_States[m_ActiveState]->OnLogicTick(delta);
}
void cStateManager::GraphicsTick() {
	if (m_States.empty()) {
		S_LogError("cStateManager", "No states found");
		return;
	}
	if (!m_States[m_ActiveState]->IsStarted()) {
		UpdateActiveState();
		if (m_ActiveState == 0) {
			return;
		}
	}
	m_States[m_ActiveState]->OnGraphicsTick();
}

void cStateManager::UpdateActiveState() {
	m_ActiveState = 0;
	for (int i = (int)m_States.size() - 1; i >= 0; i--) {
		if (m_States[i]->IsStarted() && m_ActiveState == 0) {
			m_ActiveState = i;
		} else if (m_States[i]->IsStoped()) {
			delete m_States[i];
			m_States.erase(m_States.begin() + i);
		}
	}
}

} /* namespace StormFramework */