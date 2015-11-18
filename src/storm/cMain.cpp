#include "cMain.h"

namespace StormFramework {

cMain::cMain() : m_LastGraphics(0), 
                 m_LastLogic(0), 
                 m_Delta(0),
                 m_TargetLogicTicks(30),
                 m_TargetGraphicsTicks(60),
                 m_IsRunning(false) {
}
cMain::~cMain() {
    S_LogInfo("cMain", "Framework finished");
}

void cMain::Start() {
    m_IsRunning = true;

    while (m_IsRunning) {
        TickInternal();
        if (S_GetEventManager().ToQuit()) {
            m_IsRunning = false;
        }
        // TODO: Make this batter...
        // Check if logic ore graphics are late, and if so,
        // do not call STORM_SLEEP at the end
        // else calculate precise sleep time
        if (STORM_TIME - m_LastLogic >= (float)1000 / m_TargetLogicTicks) {
            m_Delta = STORM_TIME - m_LastLogic;
            LogicTick();
            m_LastLogic = STORM_TIME;
        }
        if (STORM_TIME - m_LastGraphics >= (float)1000 / m_TargetGraphicsTicks) {
            GraphicsTick();
            m_LastGraphics = STORM_TIME;
        }

        STORM_SLEEP(1);
    }
    S_GetStateManager().Clear();
    S_LogInfo("cMain", "Main loop ended successfully");
}

// Private methods
void cMain::TickInternal() {
    S_TickEvents();
    S_TickCallbakcs();
}
void cMain::LogicTick() {
    cStateManager &sm = S_GetStateManager();
    sm.LogicTick(m_Delta);
}
void cMain::GraphicsTick() {
    cStateManager &sm = S_GetStateManager();
    sm.GraphicsTick();
    S_TickGraphics();
}

};