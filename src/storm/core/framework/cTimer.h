/* 
 * File:   cFrameworkMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 8:41 PM
 */
#ifndef CSTORMTIMER_H__
#define CSTORMTIMER_H__
#include <iostream>
#include "cFrameworkMain.h"

class cStormTimer {
public:
    cStormTimer() : m_StartTime(STORM_TIME), m_Interval(0) { }
    cStormTimer(uint32_t interval) : m_StartTime(STORM_TIME), 
                                     m_Interval(interval) { }

    void Start() { m_StartTime = STORM_TIME; }
    void Restart() { m_StartTime = STORM_TIME; }
    void Stop() { m_StartTime = 0; }

    bool IsTimeUp() { 
        if (m_Interval > 0) {
            return STORM_TIME - m_StartTime >= m_Interval; 
        }
        return false;
    }

    void SetInterval(uint32_t interval) { m_Interval = interval; }
    uint32_t GetInterval() { return m_Interval; }
    uint32_t GetStartTime() { return m_StartTime; }
private:
    /* Holds time when was this timer last started/restarted */
    uint32_t m_StartTime;
    /* Interval on what this timer will tick */
    uint32_t m_Interval;
};

#endif