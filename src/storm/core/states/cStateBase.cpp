#include "cStateBase.h"
#include "statesMain.h"

namespace StormFramework {

void cStateBase::End() {
	OnShutdown();
	m_State = STOPED;
	GetStateManager().UpdateActiveState();
}
void cStateBase::Pause() {
	OnPause();
	m_State = PAUSED;
	GetStateManager().UpdateActiveState();
}

void cStateBase::Resume() {
	OnResume();
	m_State = STARTED;
	GetStateManager().UpdateActiveState();
}

} /* namespace StormFramework */