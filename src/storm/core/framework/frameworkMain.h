/* 
 * File:   frameworkMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:23 PM
 */

#ifndef FRAMEWORKMAIN_H__
#define FRAMEWORKMAIN_H__
#include <iostream>
#include "sPrimitives.h"
#include "cTime.h"

#define STORM_TIME StormFramework::cTime::Get()
#define STORM_SLEEP(time) StormFramework::cTime::SleepMs(time)

/* Logging methods */
void S_LogInfo(const std::string &cName, const std::string &msg, ...);
void S_LogWarning(const std::string &cName, const std::string &msg, ...);
void S_LogError(const std::string &cName, const std::string &msg, ...);
void S_LogDebug(const std::string &cName, const std::string &msg, ...);

#endif /* FRAMEWORKMAIN_H__ */