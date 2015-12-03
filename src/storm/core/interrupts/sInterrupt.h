/* 
 * File:   sinterrupt.h
 * Author: master312
 *
 * Created on November 02, 2015, 9:09 PM
 */
#ifndef SCALLBACK_H__
#define SCALLBACK_H__
#include <functional>
#include <iostream>
#include "../framework/frameworkMain.h"

typedef std::function<int()> S_Callback;

namespace StormFramework {

struct sinterrupt {
    /* Interval on what this callback is called (ms) */
    uint32_t m_Interval;
    /* Last time when this interval was called */
    uint32_t m_LastTime;
    /* Callback method */
    S_Callback m_Callback;

    sinterrupt(uint32_t time, S_Callback callback) : 
                m_Interval(time),
                m_LastTime(STORM_TIME), 
                m_Callback(callback) { }
    sinterrupt(S_Callback callback) : 
                m_Interval(1),
                m_LastTime(STORM_TIME),
                m_Callback(callback) { }

    /* Returns true if callback is ready to be called */
    bool IsReady() {
        return STORM_TIME - m_LastTime >= m_Interval;
    }

    void Call() { 
        m_LastTime = STORM_TIME;
        m_Callback(); 
    }
};

} /* namespace StormFramework  */
#endif /* SCALLBACK_H__ */