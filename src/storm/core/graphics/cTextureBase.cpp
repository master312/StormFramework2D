#include "cTextureBase.h"
#include "../../core/interrupts/interruptsMain.h"
#include "cTextureManager.h"
#include "graphicsMain.h"

namespace StormFramework {

void cTextureBase::IncUsage() {
    m_Usage++;
    if (m_DeleteCbId > 0) {
        S_RemoveCB(m_DeleteCbId);
        m_DeleteCbId = 0;
    }
}

void cTextureBase::DecUsage() {
    if (m_Usage == 0)
        return;

    m_Usage--;
    if (m_Usage <= 0 && m_DeleteCbId == 0) {
        // Texture not in use. Delete id after timeout
        m_DeleteCbId = S_AddDelayedCB(new STORM_INTERRUPT(STORM_TEXTURE_TIMEOUT, 
                                                         cTextureBase, 
                                                         DeleteCb,
                                                         this));
    }
}

int cTextureBase::DeleteCb() {
    m_DeleteCbId = 0;
    if (m_Usage <= 0) {
        S_GetTextureManager().Unload(this);
    }
    return 1;
}

} /* namespace StormFramework */