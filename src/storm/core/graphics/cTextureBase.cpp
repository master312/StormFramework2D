#include "cTextureBase.h"
#include "../../callback/callbackMain.h"
#include "cTextureManager.h"
#include <functional>
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
    m_Usage--;
    if (m_Usage <= 0 && m_DeleteCbId == 0) {
        // Texture not in use. Delete id after timeout
        m_DeleteCbId = S_AddDelayedCB(new StormCB(STORM_TEXTURE_TIMEOUT,
                        std::bind(&cTextureBase::DeleteCb, this)));
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