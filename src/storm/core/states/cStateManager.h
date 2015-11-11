/* 
 * File:   cStateManager.h
 * Author: master312
 *
 * Created on November 2, 2015, 7:04 PM
 */
#ifndef CSTATEMANAGER_H__
#define CSTATEMANAGER_H__
#include <iostream>
#include <vector>
#include "../../defines.h"
#include "cStateBase.h"
#include "../framework/frameworkMain.h"

namespace StormFramework {

class cStateManager {
public:
	cStateManager();
	~cStateManager();

	/* Adds state to state manager */
	/* Last added cStateBase with state be CREATED will be active */
	/* cStateBase object will be automatically deleted when it's */
	/* state is set to STOPED */
	void PushState(cStateBase *state);
	
	void LogicTick(uint32_t &delta);
	void GraphicsTick();

	void UpdateActiveState();
private:
	std::vector<cStateBase*> m_States;
	uint32_t m_ActiveState;

};

} /* namespace StormFramework */
#endif /* CSTATEMANAGER_H__ */