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
#include "cFileSystem.h"

namespace StormFramework {

class cBinaryFile {
public:
    cBinaryFile();
    cBinaryFile(const std::string &filename, bool isWrite = false);
    ~cBinaryFile();

    /* Opens binary file. Returns < 0 on error */
    int Open(const std::string &filename, bool isWrite = false);
    /* Closes file */
    void Close();

    /* Jump to position(offset) in file. @loc is location in bytes */
    void Seek(uint32_t num);

    /* Data reading methods */
    int32_t ReadInt32();
    uint32_t ReadUint32();
    int16_t ReadInt16(); // - short
    uint16_t ReadUint16(); // - short
    float ReadFloat();
    char ReadByte();
    std::string ReadString();
    std::string ReadString(uint32_t len);
    sRect ReadSRect();

    /* Data writing methods */
    void WriteInt32(int32_t var);
    void WriteUint32(uint32_t var);
    void WriteInt16(int16_t var);
    void WriteUint16(uint16_t var);
    void WriteFloat(float var);
    void WriteByte(char var);
    void WriteString(const std::string &var);
    void WriteSRect(sRect rect);

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

} /* namespace StormFramework { */

typedef StormFramework::cBinaryFile StormBinaryFile;

#endif /* CBINARYFILE_H__ */