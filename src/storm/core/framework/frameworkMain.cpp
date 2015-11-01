#include "frameworkMain.h"
#include "cLogger.h"

void S_LogInfo(const std::string &cName, const std::string &msg, ...) {
    va_list ap;
    va_start(ap, msg);
    StormFramework::cLogger::LogInfo(cName, msg, ap);
    va_end(ap);
}
void S_LogWarning(const std::string &cName, const std::string &msg, ...) {
    va_list ap;
    va_start(ap, msg);
    StormFramework::cLogger::LogWarn(cName, msg, ap);
    va_end(ap);
}
void S_LogError(const std::string &cName, const std::string &msg, ...) {
    va_list ap;
    va_start(ap, msg);
    StormFramework::cLogger::LogErr(cName, msg, ap);
    va_end(ap);
}
void S_LogDebug(const std::string &cName, const std::string &msg, ...) {
    va_list ap;
    va_start(ap, msg);
    StormFramework::cLogger::LogDebug(cName, msg, ap);
    va_end(ap);
}