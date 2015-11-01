#include "cLogger.h"

namespace StormFramework {

void cLogger::LogInfo(const std::string &cName, 
                      const std::string &msg, va_list ap) {
    SetTerminalColor((char*)STORM_LOGCOLOR_INFO);
    std::cout << "INFO ";
    SetTerminalColor((char*)STORM_LOGCOLOR_CLASS);
    std::cout << cName << ": ";
    SetTerminalColor((char*)STORM_LOGCOLOR_INFO);
    size_t n = std::count(msg.begin(), msg.end(), '%');
    int count = static_cast<int>(n);
    PrintArgsText(msg, count, ap);
}
void cLogger::LogWarn(const std::string &cName, 
                      const std::string &msg, va_list ap) {
    SetTerminalColor((char*)STORM_LOGCOLOR_WARNING);
    std::cout << "WARNING ";
    SetTerminalColor((char*)STORM_LOGCOLOR_CLASS);
    std::cout << cName << ": ";
    SetTerminalColor((char*)STORM_LOGCOLOR_WARNING);
    size_t n = std::count(msg.begin(), msg.end(), '%');
    int count = static_cast<int>(n);
    PrintArgsText(msg, count, ap);
}
void cLogger::LogErr(const std::string &cName, 
                     const std::string &msg, va_list ap) {
    SetTerminalColor((char*)STORM_LOGCOLOR_ERROR);
    std::cout << "ERROR ";
    SetTerminalColor((char*)STORM_LOGCOLOR_CLASS);
    std::cout << cName << ": ";
    SetTerminalColor((char*)STORM_LOGCOLOR_ERROR);
    size_t n = std::count(msg.begin(), msg.end(), '%');
    int count = static_cast<int>(n);
    PrintArgsText(msg, count, ap);
}
void cLogger::LogDebug(const std::string &cName, 
                       const std::string &msg, va_list ap) {
    SetTerminalColor((char*)STORM_LOGCOLOR_DEBUG);
    std::cout << "DEBUG ";
    SetTerminalColor((char*)STORM_LOGCOLOR_CLASS);
    std::cout << cName << ": ";
    SetTerminalColor((char*)STORM_LOGCOLOR_DEBUG);
    size_t n = std::count(msg.begin(), msg.end(), '%');
    int count = static_cast<int>(n);
    PrintArgsText(msg, count, ap);
}
//Private
void cLogger::SetTerminalColor(char *col) {
#ifdef OS_LINUX
    std::cout << col;
#elif OS_WINDOWS
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (uint)termColor);
#else
    std::cout << "cLogger Platform not supported!" << std::endl;
#endif
}
void cLogger::ResetTerminalColor() {
#ifdef OS_LINUX
    std::cout << STORM_LOGCOLOR_DEFAULT;
#elif OS_WINDOWS
#else
    std::cout << "cLogger Platform not supported!" << std::endl;
#endif
}

void cLogger::PrintArgsText(const std::string &text, int count, va_list ap) {
    if (count <= 0) {
        std::cout << text << std::endl;
        return;
    }
    
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '%') {
            switch (text[i + 1]) {
                case 'd':   //Int
                    std::cout << va_arg(ap, int);
                    break;
                case 's':
                    std::cout << va_arg(ap, char*);
                    break;
                case 'f':
                    std::cout << va_arg(ap, float);
                    break;
                default:
                    break;
            }
            i++;    
        } else {
            std::cout << text[i];
        }
    }
    std::cout << std::endl;
}

}   /* namespace StormFramework */

