#pragma once

#define DEFAULT_PACKET_SIZE 0xFFFF

class Packet{
public:
    Packet();
    ~Packet();
    Packet(Packet&& packet);

    /// @brief Sets the position to the buffer at index 0 to start reading
    void PrepareRead();
public:
    void WriteInt32(int32_t data);
    void WriteUInt32(uint32_t data);
    void WriteInt16(int16_t data);
    void WriteUInt16(uint16_t data);
    void WriteInt8(int8_t data);
    void WriteUInt8(uint8_t data);
    void WriteString(const char* string);
public:
    int32_t ReadInt32();
    uint32_t ReadUInt32();
    int16_t ReadInt16();
    uint16_t ReadUInt16();
    int8_t ReadInt8();
    uint8_t ReadUInt8();
    std::string ReadString();
public:
    uint8_t*  GetData() const noexcept{return m_Data;}
    size_t GetSize() const noexcept{return m_Size;}
    bool CanDeleteData() const noexcept{return m_CanDeleteData;}
private:
    uint8_t* m_Data = nullptr;
    size_t m_Size = 0;
    bool m_CanDeleteData = false;

    //The position to read/write
    size_t m_Pos = 0;
};