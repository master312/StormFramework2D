/* 
 * File:   cMain.h
 * Author: master312
 *
 * Created on November 8, 2015, 8:46 PM
 */
#ifndef CSTORMMAIN_H__
#define CSTORMMAIN_H__
#include <iostream>
#include "core/framework/frameworkMain.h"
#include "core/graphics/graphicsMain.h"
#include "core/events/eventsMain.h"
#include "core/events/cEventManager.h"
#include "core/states/statesMain.h"
#include "animation/animationMain.h"
#include "defines.h"

namespace StormFramework {

class cMain {
public:
	cMain();
	~cMain();

	/* Starts the main loop ticking */
	void Start();
	/* Stops the main loop */
	void Stop() { m_IsRunning = false; }

	void SetLogicTickLimit(uint32_t ticks) { m_TargetLogicTicks = ticks; }
	void SetGraphicsTickLimit(uint32_t ticks) { m_TargetGraphicsTicks = ticks; }
	uint32_t &GetDelta() { return m_Delta; }
	bool IsRunning() { return m_IsRunning; }
private:
	uint32_t m_LastGraphics;
	uint32_t m_LastLogic;
	uint32_t m_Delta;

	uint32_t m_TargetLogicTicks;
	uint32_t m_TargetGraphicsTicks;

	bool m_IsRunning;

	void LogicTick();
	void GraphicsTick();
};


} /* namespace StormFramework */
#endif /* CSTORMMAIN_H__ */