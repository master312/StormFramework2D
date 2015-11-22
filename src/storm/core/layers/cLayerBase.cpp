#include "cLayerBase.h"
#include "layersMain.h"

namespace StormFramework {

void cLayerBase::End() {
    OnShutdown();
    m_State = STOPED;
    S_GetLayerManager().UpdateActiveLayer();
}
void cLayerBase::Pause() {
    OnPause();
    m_State = PAUSED;
    S_GetLayerManager().UpdateActiveLayer();
}

void cLayerBase::Resume() {
    OnResume();
    m_State = STARTED;
    S_GetLayerManager().UpdateActiveLayer();
}

} /* namespace StormFramework */