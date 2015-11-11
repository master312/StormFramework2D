/* 
 * File:   cStateBase.h
 * Author: master312
 *
 * Created on November 2, 2015, 6:40 PM
 */
#ifndef CSTATEBASE_H__
#define CSTATEBASE_H__
#include <iostream>
#include "../../defines.h"

namespace StormFramework {

enum eStateBaseState {
    CREATED = 1,
    INITED = 2,
    STARTED = 3,
    PAUSED = 4,
    STOPED = 5
};

class cStateBase {
public:
	cStateBase() : m_State(CREATED) { }
	virtual ~cStateBase() { }

	/* Called on state initialization */
	virtual void OnInit() { }
	/* Called on graphics tick */
	virtual void OnGraphicsTick() { }
	/* Called on logic tick */
	virtual void OnLogicTick(uint32_t &delta) { }
	/* Called on new event */
	virtual void OnEvent() { }
	/* Called when state is paused */
	virtual void OnPause() { }
	/* Called when state was resumed */
	virtual void OnResume() { }
	/* Called when state is ended, just before state object deletion */
	virtual void OnShutdown() { }

	/* This function will end state, and delete state object */
	/* After OnShutdown() is called */
	void End();
	/* Pauses state */
	void Pause();
	/* Resumes state */
	void Resume();

	eStateBaseState &GetState() { return m_State; }
	void SetState(const eStateBaseState &state) { m_State = state; }

	bool IsCreated() { return m_State == CREATED; }
	bool IsInited() { return m_State == INITED; }
	bool IsStarted() { return m_State == STARTED; }
	bool IsPaused() { return m_State == PAUSED; }
	bool IsStoped() { return m_State == STOPED; }
protected:
	eStateBaseState m_State;
};

} /* namespace StormFramework  */
#endif /* CSTATEBASE_H__ */