/* 
 * File:   cTime.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:58 PM
 */

#ifndef CTIME_H__
#define CTIME_H__
#include <iostream>
#include "../../defines.h"

namespace StormFramework {
    
#ifdef OS_LINUX
#include <sys/time.h>
#include <unistd.h>
#elif OS_WINDOWS
#include <windows.h>
#endif

static uint64_t cTime_StartTime;

class cTime {
public:
    static void Start() {
        cTime_StartTime = cTime::GetTimeInMs();
    }
    static uint32_t Get() {
        return (uint32_t)(GetTimeInMs() - cTime_StartTime);
    }
    static void SleepMs(uint32_t ms) { 
    #ifdef OS_LINUX
        usleep(ms * 1000);
    #elif OS_WINDOWS
        Sleep(ms);
    #else
        std::cout << "cTime platform not supported 1" << std::endl;
    #endif
    }
    static uint64_t GetTimeInMs() {
    #ifdef OS_LINUX
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return tp.tv_sec * 1000 + tp.tv_usec / 1000;
    #elif OS_WINDOWS
        SYSTEMTIME time;
        GetSystemTime(&time);
        return (uint64_t)(time.wSecond * 1000) + time.wMilliseconds;
    #else
        std::cout << "cTime platform not supported 2.2" << std::endl;
    #endif
    }
};

} /* namespace StormFramework */
#endif  /* CTIME_H__ */

