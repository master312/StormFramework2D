/* 
 * File:   cLogger.h
 * Author: master312
 *
 * Created on September 27, 2015, 2:23 AM
 */

#ifndef CLOGGER_H__
#define CLOGGER_H__
#include "../../defines.h"
#include <iostream>
#include <cstdarg>

#ifdef OS_LINUX
 #define STORM_LOGCOLOR_DEFAULT "\033[0m"
 #define STORM_LOGCOLOR_INFO    "\033[32m"
 #define STORM_LOGCOLOR_WARNING "\033[33m"
 #define STORM_LOGCOLOR_ERROR   "\033[31m"
 #define STORM_LOGCOLOR_CLASS   "\033[36m"
 #define STORM_LOGCOLOR_DEBUG   "\033[34m"
#elif OS_WINDOWS 
 #include <windows.h>
 #define STORM_LOGCOLOR_DEFAULT (uint)(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
 #define STORM_LOGCOLOR_INFO    (uint)(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
 #define STORM_LOGCOLOR_WARNING (uint)(FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
 #define STORM_LOGCOLOR_ERROR   (uint)(FOREGROUND_RED|FOREGROUND_INTENSITY)
 #define STORM_LOGCOLOR_CLASS   (uint)(FOREGROUND_GREEN|FOREGROUND_INTENSITY)
 #define STORM_LOGCOLOR_DEBUG   (uint)(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#endif

namespace StormFramework {

class cLogger {
public:
    static void LogInfo(const std::string &cName, 
                        const std::string &msg, va_list ap);
    static void LogWarn(const std::string &cName, 
                        const std::string &msg, va_list ap);
    static void LogErr(const std::string &cName, 
                       const std::string &msg, va_list ap);
    static void LogDebug(const std::string &cName, 
                         const std::string &msg, va_list ap);

    static void SetTerminalColor(char *col);
    static void ResetTerminalColor();
    static void PrintArgsText(const std::string &text, int count, va_list ap);
};

} /* namespace StormFramework */

#endif  /* CLOGGER_H */

