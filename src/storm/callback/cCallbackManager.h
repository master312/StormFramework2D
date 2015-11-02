/* 
 * File:   cCallbackManager.h
 * Author: master312
 *
 * Created on November 02, 2015, 9:01 PM
 * TODO: Features:
 *  -Methods are indexed by name (std::string)
 *  -Call method after specified time only once
 *  -Call method on interval
 *  -Call method on event
 *  -Store callback by name, and call it manually
 *  -Functions must be of type void name(void *data)
 *   or int name(void *data) if 'on interval' callback.
 *   If 'on interval' callback return < 0, than its removed
 *   from timed callback system.
 *  -On manually calling callback by name, caller
 *   should be able to specify data that is passed to method
 *
 * TODO::::::::::::::TODO::::::::::::TODO:::::::::::TODO:::::::
 *    !!TEST THIS CLASS!!
 */
#ifndef CCALLBACKMANAGER_H__
#define CCALLBACKMANAGER_H__
#include <iostream>
#include <map>
#include <vector>
#include "../core/framework/frameworkMain.h"
#include "../defines.h"

namespace StormFramework {

struct sIntervalCallback;
struct sManualCallback;

class cCallbackManager {
public:
	cCallbackManager() { }
	~cCallbackManager();

	void Tick();

	void AddIntervalCallback(const std::string &name,
							 sIntervalCallback *callback);
	void AddManulaCallback(const std::string &name,
							sManualCallback *callback);
	void AddDelayedCallback(sManualCallback *callback);
	
	void RemoveCallback(const std::string &name);
private:
	std::map<std::string, sIntervalCallback*> m_IntervalCallbacks;
	std::map<std::string, sManualCallback*> m_ManualCallbacks;
	std::vector<sManualCallback*> m_DelayedCallbacks;

	/* This method returns true, if @name already exists */
	/* in any of callback std::map-s */ 
	bool IfExists(const std::string &name);
};


} /* namespace StormFramework */
#endif /* CCALLBACKMANAGER_H__ */