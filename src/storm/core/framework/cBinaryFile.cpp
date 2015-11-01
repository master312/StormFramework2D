#include "cBinaryFile.h"
#include "cData.h"

using namespace StormFramework;

cStormBinaryFile::cStormBinaryFile() : m_WriteMode(false) { }
cStormBinaryFile::cStormBinaryFile(const std::string &filename, 
                                   bool isWrite /*= false */) {
    Open(filename, isWrite);
}
cStormBinaryFile::~cStormBinaryFile() {
    if (m_File.is_open()){
        m_File.close();
    }
}

int cStormBinaryFile::Open(const std::string &filename,
                           bool isWrite /* = false */) {
    m_WriteMode = isWrite;
    m_Filename = filename;

    if (m_WriteMode) {
        m_File.open(m_Filename.c_str(), std::ios::binary | std::fstream::out);
    } else {
        m_File.open(m_Filename.c_str(), std::ios::binary | std::fstream::in);
    }

    if (!m_File.is_open()) {
        S_LogError("cStormBinaryFile", 
                   "Could not open binary file '%s'", m_Filename.c_str());
        return -1;
    }

    m_CurLoc = 0;

    return 1;
}
void cStormBinaryFile::Close() {
    if (m_File.is_open()) {
        m_File.close();
    }
}

void cStormBinaryFile::Seek(uint32_t num) {
    std::cout << "TODO:  Binary file seek() method" << std::endl;
}

int cStormBinaryFile::ReadInt() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 4);
    m_CurLoc += 4;
    return cData::ByteToInt((char*)m_Buffer, 0);
}
short cStormBinaryFile::ReadShort() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 2);
    m_CurLoc += 2;
    return cData::ByteToShort((char*)m_Buffer, 0);
}
float cStormBinaryFile::ReadFloat() {
    if (m_WriteMode) return 0.0f;
    m_File.read(m_Buffer, 4);
    m_CurLoc += 4;
    return cData::ByteToFloat((char*)m_Buffer, 0);
}
char cStormBinaryFile::ReadByte() {
    if (m_WriteMode) return '0';
    m_File.read(m_Buffer, 1);
    m_CurLoc += 1;
    return m_Buffer[0];
}
std::string cStormBinaryFile::ReadString() {
    if (m_WriteMode) return "0";
    uint strLen = 0;
    m_File.read(m_Buffer, 4);
    strLen = (uint)cData::ByteToInt(m_Buffer, 0);
    char* tmpString = new char[strLen + 1];
    m_File.read(tmpString, strLen);
    std::string tmpS(tmpString);
    delete [] tmpString;
    m_CurLoc += strLen;
    return tmpS;
}
std::string cStormBinaryFile::ReadString(uint32_t len) {
    if (m_WriteMode) return "0";
    char* tmpString = new char[len + 1];
    m_File.read(tmpString, len);
    std::string tmpS(tmpString);
    delete [] tmpString;
    m_CurLoc += len;
    return tmpS;
}

void cStormBinaryFile::WriteInt(int var) {
    if (!m_WriteMode) return;
    cData::IntToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 4);
    m_CurLoc += 4;
}
void cStormBinaryFile::WriteShort(short var) {
    if (!m_WriteMode) return;
    cData::ShortToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 2);
    m_CurLoc += 2;
}
void cStormBinaryFile::WriteFloat(float var) {
    if (!m_WriteMode) return;
    cData::FloatToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 4);
    m_CurLoc += 4;
}
void cStormBinaryFile::WriteByte(char var) {
    if (!m_WriteMode) return;
    m_File.write(m_Buffer, 1);
    m_CurLoc += 1;
}
void cStormBinaryFile::WriteString(std::string var) {
    if (!m_WriteMode) return;
    WriteInt(var.size());
    m_File.write(var.c_str(), var.size());
    m_CurLoc += var.size();
}

bool cStormBinaryFile::IsOpen() {
    return m_File.is_open();
}
bool cStormBinaryFile::IsEof() {
    return m_File.eof();
}