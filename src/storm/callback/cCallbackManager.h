/* 
 * File:   cCallbackManager.h
 * Author: master312
 *
 * Created on November 02, 2015, 9:01 PM
 * Features:
 *  -Methods are indexed by name (std::string)
 *  -Call method after specified time only once
 *  -Call method on interval
 *  -TODO: Call method on event ??? or this is in EVENT MANAGER ???
 *  -Functions must be of type 'int name()''
 *   If 'on interval' callback method return < 0, it will be removed
 *   from timed callback system.
 */
#ifndef CCALLBACKMANAGER_H__
#define CCALLBACKMANAGER_H__
#include <iostream>
#include <map>
#include <vector>
#include "../core/framework/frameworkMain.h"
#include "../defines.h"

namespace StormFramework {

struct sCallback;

class cCallbackManager {
public:
    ~cCallbackManager();
    void Clear();

    void Tick();

    void AddIntervalCallback(const std::string &name,
                             sCallback *callback);
    void AddDelayedCallback(sCallback *callback);

    void Remove(const std::string &name);
private:
    std::map<std::string, sCallback*> m_IntervalCallbacks;
    std::vector<sCallback*> m_DelayedCallbacks;

    /* This method returns true, if @name already exists */
    /* in any of callback std::map-s */ 
    bool IfExists(const std::string &name);
};


} /* namespace StormFramework */
#endif /* CCALLBACKMANAGER_H__ */