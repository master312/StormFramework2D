#include "cMain.h"
#include "core/graphics/cGraphicsManager.h"
#include "core/interrupts/cInterruptManager.h"
#include "animations/cAnimationManager.h"

namespace StormFramework {

cMain::cMain() : m_LastGraphics(0), 
                 m_LastLogic(0), 
                 m_Delta(0),
                 m_TargetLogicTicks(30),
                 m_TargetGraphicsTicks(1000),
                 m_CurFps(0),
                 m_TmpFps(0),
                 m_TmpFpsCount(0),
                 m_FpsAvgInterval(500),
                 m_LastFpsTime(0),
                 m_IsRunning(false) {

}
cMain::~cMain() {
    S_LogInfo("cMain", "Framework finished");
}

void cMain::Start() {
    m_IsRunning = true;

    m_LastFpsTime = STORM_TIME;
    while (m_IsRunning) {
        TickInternal();
        if (S_GetEventManager().ToQuit()) {
            m_IsRunning = false;
        }
        // TODO: Make this batter...
        // Check if logic ore graphics are late, and if so,
        // do not call STORM_SLEEP at the end
        // else calculate precise sleep time
        if (STORM_TIME - m_LastLogic >= 1000 / m_TargetLogicTicks) {
            m_Delta = STORM_TIME - m_LastLogic;
            LogicTick();
            m_LastLogic = STORM_TIME;
        }
        if (STORM_TIME - m_LastGraphics >= 1000 / m_TargetGraphicsTicks) {
            GraphicsTick();
            m_TmpFps += (float)1000 / (STORM_TIME - m_LastGraphics);
            m_TmpFpsCount++;
            m_LastGraphics = STORM_TIME;
        }
        // Handles FPS averaging stuff 
        if (STORM_TIME - m_LastFpsTime >= m_FpsAvgInterval) {
            CalcAvgFps();
            std::cout << "OBJ Count: " << S_GetGraphicsManager().GetOnScreenCount() << " FPS: " << m_CurFps << std::endl;
            m_LastFpsTime = STORM_TIME;
        }
        STORM_SLEEP(1);
    }
    
    S_GetLayerManager().Clear();
    S_GetAnimationManager().Clear();
    S_GetGraphicsManager().DeInitialize();
    S_LogInfo("cMain", "Main loop ended successfully");
}

// Private methods
void cMain::TickInternal() {
    S_GetEventManager().Tick();
    S_GetCallbackManager().Tick();
}
void cMain::LogicTick() {
    cLayerManager &sm = S_GetLayerManager();
    cAnimationManager &am = S_GetAnimationManager();
    sm.LogicTick(m_Delta);
    am.Tick(m_Delta);
}
void cMain::GraphicsTick() {
    cLayerManager &sm = S_GetLayerManager();
    sm.GraphicsTick();
    S_GetGraphicsManager().Tick();
}
void cMain::CalcAvgFps() {
    m_CurFps = (m_TmpFps / m_TmpFpsCount);
    m_TmpFpsCount = 0;
    m_TmpFps = 0;
}

};