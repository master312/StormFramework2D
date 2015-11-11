#include "cStateBase.h"
#include "statesMain.h"

namespace StormFramework {

void cStateBase::End() {
	OnShutdown();
	m_State = STOPED;
	S_GetStateManager().UpdateActiveState();
}
void cStateBase::Pause() {
	OnPause();
	m_State = PAUSED;
	S_GetStateManager().UpdateActiveState();
}

void cStateBase::Resume() {
	OnResume();
	m_State = STARTED;
	S_GetStateManager().UpdateActiveState();
}

} /* namespace StormFramework */