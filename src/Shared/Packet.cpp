#include "pch.h"
#include "Packet.h"
#include "Core/Logger.h"

Packet::Packet(){
    m_Size = DEFAULT_PACKET_SIZE;
    m_Data = new uint8_t[m_Size];
    m_CanDeleteData = true;
}
Packet::~Packet(){
    if(m_CanDeleteData)
        delete m_Data;
}
Packet::Packet(Packet&& packet){
    m_Data = packet.m_Data;
    m_Size = packet.m_Size;
    m_CanDeleteData = packet.m_CanDeleteData;
    packet.m_Data = nullptr;
    packet.m_Size = 0;
    packet.m_CanDeleteData = false;
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
    m_Data[m_Pos] = (data >> 8) & 0xFF;
    m_Pos += sizeof(int8_t);
}
void Packet::WriteUInt8(uint8_t data){
    m_Data[m_Pos] = data >> 8 & 0xFF;
    m_Pos += sizeof(uint8_t);
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
#pragma endregion