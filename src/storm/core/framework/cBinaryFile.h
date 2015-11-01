/* 
 * File:   cBinaryFile.h
 * Author: master312
 *
 * Created on October 18, 2015, 5:23 PM
 */
#ifndef CSTORMBINARYFILE_H__
#define CSTORMBINARYFILE_H__
#include <iostream>
#include <fstream>
#include "frameworkMain.h"

class cStormBinaryFile {
public:
    cStormBinaryFile();
    cStormBinaryFile(const std::string &filename, bool isWrite = false);
    ~cStormBinaryFile();

    /* Opens binary file. Returns < 0 on error */
    int Open(const std::string &filename, bool isWrite = false);
    /* Closes file */
    void Close();

    /* Jump to position(offset) in file. @loc is location in bytes */
    void Seek(uint32_t num);

    /* Data reading methods */
    int ReadInt();
    short ReadShort();
    float ReadFloat();
    char ReadByte();
    std::string ReadString();
    std::string ReadString(uint32_t len);

    /* Data writing methods */
    void WriteInt(int var);
    void WriteShort(short var);
    void WriteFloat(float var);
    void WriteByte(char var);
    void WriteString(std::string var);

    bool IsOpen();
    bool IsEof();

    uint32_t GetCurLoc() { return m_CurLoc; }
private:
    std::string m_Filename;
    /* Current location pointer */
    uint32_t m_CurLoc;
    /* fstream file object */
    std::fstream m_File;
    /* Temporary bytes buffer */
    char m_Buffer[8];
    /* Is file in write mode */
    bool m_WriteMode;
};

#endif /* CBINARYFILE_H__ */