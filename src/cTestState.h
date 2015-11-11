#pragma once
#include <iostream>
#include "storm/core/states/statesMain.h"


class cTestState : public StormState {
public:
	cTestState();
	~cTestState();

	/* Called on state initialization */
	void OnInit();
	/* Called on graphics tick */
	void OnGraphicsTick();
	/* Called on logic tick */
	void OnLogicTick(uint32_t &delta);
	/* Called on new event */
	void OnEvent(uint32_t &event);
	/* Called when state is paused */
	void OnPause();
	/* Called when state was resumed */
	void OnResume();
	/* Called when state is ended, just before state object deletion */
	void OnShutdown();
};