#include "cBinaryFile.h"
#include "cBinary.h"

namespace StormFramework {

cBinaryFile::cBinaryFile() : m_WriteMode(false) { }
cBinaryFile::cBinaryFile(const std::string &filename, 
                                   bool isWrite /*= false */) {
    Open(filename, isWrite);
}
cBinaryFile::~cBinaryFile() {
    if (m_File.is_open()){
        m_File.close();
    }
}

int cBinaryFile::Open(const std::string &filename,
                           bool isWrite /* = false */) {
    
    m_WriteMode = isWrite;
    m_Filename = filename;
    
    cFileSystem::ConvertPath(m_Filename);

    if (m_WriteMode) {
        m_File.open(m_Filename.c_str(), std::ios::binary | std::fstream::out);
    } else {
        m_File.open(m_Filename.c_str(), std::ios::binary | std::fstream::in);
    }

    if (!m_File.is_open()) {
        S_LogError("cBinaryFile", 
                   "Could not open binary file '%s'", m_Filename.c_str());
        return -1;
    }

    m_CurLoc = 0;

    return 1;
}
void cBinaryFile::Close() {
    if (m_File.is_open()) {
        m_File.close();
    }
}

void cBinaryFile::Seek(uint32_t num) {
    std::cout << "TODO:  Binary file seek() method" << std::endl;
}

int32_t cBinaryFile::ReadInt32() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 4);
    m_CurLoc += 4;
    return cBinary::ByteToInt32((char*)m_Buffer, 0);
}
uint32_t cBinaryFile::ReadUint32() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 4);
    m_CurLoc += 4;
    return cBinary::ByteToUint32((char*)m_Buffer, 0);
}
int16_t cBinaryFile::ReadInt16() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 2);
    m_CurLoc += 2;
    return cBinary::ByteToInt16((char*)m_Buffer, 0);
}
uint16_t cBinaryFile::ReadUint16() {
    if (m_WriteMode) return 0;
    m_File.read(m_Buffer, 2);
    m_CurLoc += 2;
    return cBinary::ByteToUint16((char*)m_Buffer, 0);
}
float cBinaryFile::ReadFloat() {
    if (m_WriteMode) return 0.0f;
    m_File.read(m_Buffer, 4);
    m_CurLoc += 4;
    return cBinary::ByteToFloat((char*)m_Buffer, 0);
}
char cBinaryFile::ReadByte() {
    if (m_WriteMode) return '0';
    m_File.read(m_Buffer, 1);
    m_CurLoc += 1;
    return m_Buffer[0];
}
std::string cBinaryFile::ReadString() {
    if (m_WriteMode) return "0";
    uint32_t strLen = 0;
    m_File.read(m_Buffer, 4);
    strLen = cBinary::ByteToUint32(m_Buffer, 0);
    char* tmpString = new char[strLen];
    m_File.read(tmpString, strLen);
    tmpString[strLen] = '\0';
    std::string tmpS(tmpString);
    delete [] tmpString;
    m_CurLoc += strLen;
    return tmpS;
}
std::string cBinaryFile::ReadString(uint32_t len) {
    if (m_WriteMode) return "0";
    char* tmpString = new char[len];
    m_File.read(tmpString, len);
    tmpString[len] = '\0';
    std::string tmpS(tmpString);
    delete [] tmpString;
    m_CurLoc += len;
    return tmpS;
}
sRect cBinaryFile::ReadSRect() {
    sRect tmpRect;
    tmpRect.x = ReadInt32();
    tmpRect.y = ReadInt32();
    tmpRect.w = ReadInt32();
    tmpRect.h = ReadInt32();
    return tmpRect;
}

void cBinaryFile::WriteInt32(int32_t var) {
    if (!m_WriteMode) return;
    cBinary::Int32ToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 4);
    m_CurLoc += 4;
}
void cBinaryFile::WriteUint32(uint32_t var) {
    if (!m_WriteMode) return;
    cBinary::Uint32ToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 4);
    m_CurLoc += 4;
}
void cBinaryFile::WriteInt16(int16_t var) {
    if (!m_WriteMode) return;
    cBinary::Int16ToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 2);
    m_CurLoc += 2;
}
void cBinaryFile::WriteUint16(uint16_t var) {
    if (!m_WriteMode) return;
    cBinary::Uint16ToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 2);
    m_CurLoc += 2;
}
void cBinaryFile::WriteFloat(float var) {
    if (!m_WriteMode) return;
    cBinary::FloatToByte(var, (char*)m_Buffer);
    m_File.write(m_Buffer, 4);
    m_CurLoc += 4;
}
void cBinaryFile::WriteByte(char var) {
    if (!m_WriteMode) return;
    m_File.write(m_Buffer, 1);
    m_CurLoc += 1;
}
void cBinaryFile::WriteString(const std::string &var) {
    if (!m_WriteMode) return;
    WriteUint32(var.size());
    m_File.write(var.c_str(), var.size());
    m_CurLoc += var.size();
}
void cBinaryFile::WriteSRect(sRect rect) {
    WriteInt32((int32_t)rect.x);
    WriteInt32((int32_t)rect.y);
    WriteInt32((int32_t)rect.w);
    WriteInt32((int32_t)rect.h);
}

bool cBinaryFile::IsOpen() {
    return m_File.is_open();
}
bool cBinaryFile::IsEof() {
    return m_File.eof();
}

} /* namespace StormFramework { */