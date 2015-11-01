#include "cFileSystem.h"
#include <cstring>

namespace StormFramework {

void cFileSystem::ConvertPath(char *path) {
    #ifdef OS_WINDOWS
    for (uint i = 0; i < strlen(path); i++) {
        if (path[i] == '/') {
            path[i] = '\\';
        }
    }
    #elif OS_LINUX
    for (uint i = 0; i < strlen(path); i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
    #else
    std::cout << "cFileSystem: Platform not supported yet" << std::endl;
    #endif
}
void cFileSystem::ConvertPath(std::string &path) {
    #ifdef OS_WINDOWS
    for (uint i = 0; i < path.size(); i++) {
        if (path[i] == '/') {
            path[i] = '\\';
        }
    }
    #elif OS_LINUX
    for (uint i = 0; i < path.size(); i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
    #else
    std::cout << "cFileSystem: Platform not supported yet" << std::endl;
    #endif
}

} /* namespace StormFramework */