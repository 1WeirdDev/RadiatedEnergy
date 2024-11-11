#include "pch.h"
#include "Packet.h"
#include "Core/Logger.h"

Packet::Packet(){
    CORE_DEBUG("ALLOCATED PACKET DATA");
    m_BufferSize = DEFAULT_PACKET_SIZE;
    m_Data = new uint8_t[m_BufferSize];
    m_CanFree = true;
    m_Pos = sizeof(uint32_t) + sizeof(uint8_t);
    m_Id = 0;
}
Packet::Packet(uint8_t packetId){
    CORE_DEBUG("ALLOCATED PACKET DATA");
    m_BufferSize = DEFAULT_PACKET_SIZE;
    m_Data = new uint8_t[m_BufferSize];
    m_CanFree = true;
    m_Pos = sizeof(uint32_t) + sizeof(uint8_t);
    m_Id = packetId;
}
Packet::Packet(uint8_t* data, uint32_t size, bool canFree){
    m_Data = data;
    m_BufferSize = size;
    m_CanFree = canFree;
}
Packet::~Packet(){
    Free();
}
Packet::Packet(Packet&& packet){
    m_Data = packet.m_Data;
    m_BufferSize = packet.m_BufferSize;
    m_CanFree = packet.m_CanFree;
    m_Pos = packet.m_Pos;
    m_Id = packet.m_Id;

    packet.m_Data = nullptr;
    packet.m_BufferSize = 0;
    packet.m_CanFree = false;
    packet.m_Id = 0;
}
Packet::Packet(const Packet& packet){
    m_BufferSize = packet.m_BufferSize;
    CORE_DEBUG("ALLOCATED PACKET DATA");

    uint8_t* data = new uint8_t[m_BufferSize];
    memcpy(data, packet.m_Data, m_BufferSize);
    m_Data = data;

    m_CanFree = true;
    m_Pos = packet.m_Pos;
    m_Id = packet.m_Id;
}

Packet& Packet::operator=(const Packet& packet){
    Free();
    CORE_DEBUG("ALLOCATED PACKET DATA");
    m_BufferSize = packet.m_BufferSize;

    uint8_t* data = new uint8_t[m_BufferSize];
    memcpy(data, packet.m_Data, m_BufferSize);
    m_Data = data;

    m_CanFree = true;
    m_Pos = packet.m_Pos;
    m_Id = packet.m_Id;
    return *this;
}
Packet& Packet::operator=(Packet&& packet){
    m_BufferSize = packet.m_BufferSize;
    m_Data = packet.m_Data;
    m_CanFree = packet.m_CanFree;
    m_Id = packet.m_Id;
    m_Pos = packet.m_Pos;

    packet.m_Data = nullptr;
    packet.m_BufferSize = 0;
    packet.m_CanFree = false;
    packet.m_Pos = 0;
    packet.m_Id = 0;
    return *this;
}
void Packet::Free(){
    if(m_CanFree){
    CORE_DEBUG("DELLLOCATED PACKET DATA");
        delete m_Data;
        m_CanFree = false;
        m_BufferSize = 0;
    }
}
void Packet::SetBuffer(uint8_t* data, uint32_t size, bool canDelete){
    Free();
    m_Data = data;
    m_BufferSize = size;
    m_CanFree = canDelete;
}
void Packet::WriteHeaders(){
    uint32_t pos = m_Pos;
    m_Pos = 0;
    WriteUInt32(pos - (sizeof(uint32_t) + sizeof(uint8_t)));
    WriteUInt8(m_Id);
    m_Pos = pos;
}
void Packet::PrepareRead(){
    m_Pos = 0;
}
void Packet::PrepareWrite(){
    m_Pos = sizeof(uint32_t) + sizeof(uint8_t);
}
void Packet::WriteInt32(int32_t data){
    m_Data[m_Pos] = (data >> 24) & 0xFF;
    m_Data[m_Pos + 1] = (data >> 16) & 0xFF;
    m_Data[m_Pos + 2] = (data >> 8) & 0xFF;
    m_Data[m_Pos + 3] = data & 0xFF;
    m_Pos += sizeof(int32_t);
}
void Packet::WriteUInt32(uint32_t data){
    m_Data[m_Pos] = (data >> 24) & 0xFF;
    m_Data[m_Pos + 1] = (data >> 16) & 0xFF;
    m_Data[m_Pos + 2] = (data >> 8) & 0xFF;
    m_Data[m_Pos + 3] = data & 0xFF;
    m_Pos += sizeof(uint32_t);
}
void Packet::WriteInt16(int16_t data){
    m_Data[m_Pos] = (data >> 8) & 0xFF;
    m_Data[m_Pos + 1] = data & 0xFF;
    m_Pos += sizeof(int16_t);
}
void Packet::WriteUInt16(uint16_t data){
    m_Data[m_Pos] = data >> 8 & 0xFF;
    m_Data[m_Pos + 1] = data & 0xFF;
    m_Pos += sizeof(uint16_t);
}
void Packet::WriteInt8(int8_t data){
    m_Data[m_Pos] = data& 0xFF;
    m_Pos += sizeof(int8_t);
}
void Packet::WriteUInt8(uint8_t data){
    m_Data[m_Pos] = data & 0xFF;
    m_Pos += sizeof(uint8_t);
}

void Packet::WriteString(const char* data){
    while(true){
        int8_t byte = data[0];
        if(byte == 0)break;
        WriteInt8(byte);
        data++;
    }
    WriteInt8(0);
}
#pragma region Reading
int32_t Packet::ReadInt32(){
    int32_t data = (m_Data[m_Pos] << 24)|
    (m_Data[m_Pos + 1] << 16)|
    (m_Data[m_Pos + 2] << 8)|
    (m_Data[m_Pos + 3]);
    m_Pos += sizeof(uint32_t);
    return data;
}
uint32_t Packet::ReadUInt32(){
    uint32_t data = (m_Data[m_Pos] << 24)|
    (m_Data[m_Pos + 1] << 16)|
    (m_Data[m_Pos + 2] << 8)|
    (m_Data[m_Pos + 3]);
    m_Pos += sizeof(uint32_t);
    return data;
}
int16_t Packet::ReadInt16(){
    int16_t data = static_cast<int16_t>(m_Data[m_Pos] << 8| m_Data[m_Pos + 1]);
    (m_Data[m_Pos + 1]);
    m_Pos += sizeof(int16_t);
    return data;
}
uint16_t Packet::ReadUInt16(){
    uint16_t data = static_cast<uint16_t>(m_Data[m_Pos] << 8| m_Data[m_Pos + 1]);
    m_Pos += sizeof(int16_t);
    return data;
}
int8_t Packet::ReadInt8(){
    int8_t data = static_cast<int8_t>(m_Data[m_Pos]);
    m_Pos += sizeof(int8_t);
    return data;
}
uint8_t Packet::ReadUInt8(){
    uint8_t data = static_cast<uint8_t>(m_Data[m_Pos]);
    m_Pos += sizeof(uint8_t);
    return data;
}

std::string Packet::ReadString(){
    const char* base = (const char*)m_Data + m_Pos;
    const char* str = base;
    while(str[0] != 0x00){
        str++;
    }
    size_t len = (str - base);
    std::string string(len, 0);
    memcpy((char*)string.c_str(), base, len);
    return string;
}
#pragma endregion