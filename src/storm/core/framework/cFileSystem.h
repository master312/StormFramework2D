/* 
 * File:   cFrameworkMain.h
 * Author: master312
 *
 * Created on October 18, 2015, 7:02 PM
 */
#ifndef STORM_CFILESYSTEM_H__
#define STORM_CFILESYSTEM_H__
#include <iostream>
#include <cstring>
#include "../../defines.h"

namespace StormFramework {

class cFileSystem {
public:
    /* This method converts path of file to 
     * format that is required by current platform.
     * E.X: If platform is windows, path /data/test.dat
     * will be converted to \data\test.dat */
    static void ConvertPath(char *path);
    static void ConvertPath(std::string &path);
};

} /* namespace StormFramework */
#endif /* STORM_CFILESYSTEM_H__ */