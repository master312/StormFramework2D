/* 
 * File:   cInterruptManager.h
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
#include "../framework/frameworkMain.h"
#include "../../defines.h"

namespace StormFramework {

struct sInterrupt;

class cInterruptManager {
public:
    cInterruptManager() : m_NextId(0) { }
    ~cInterruptManager();
    void Clear();

    void Tick();

    void AddInterrupt(const std::string &name,
                             sInterrupt *callback);
    uint32_t AddDelayedCallback(sInterrupt *callback);

    /* Removes 'interval callback' by name */
    void Remove(const std::string &name);
    /* Removes delayed callback by ID */
    void Remove(uint32_t &id);
private:
    std::map<std::string, sInterrupt*> m_IntervalCallbacks;
    std::vector<sInterrupt*> m_DelayedCallbacks;
    uint32_t m_NextId;

    /* This method returns true, if @name already exists */
    /* in any of callback std::map-s */ 
    bool IfExists(const std::string &name);
};


} /* namespace StormFramework */
#endif /* CCALLBACKMANAGER_H__ */