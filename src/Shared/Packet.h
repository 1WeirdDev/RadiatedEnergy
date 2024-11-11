#pragma once

#define DEFAULT_PACKET_SIZE 0xFFFF

class Packet{
public:
    Packet(uint8_t packetId);
    ~Packet();
    Packet(Packet&& packet);

    Packet& operator=(const Packet& right);

    void Free();
    void SetBuffer(uint8_t* data, uint32_t size, bool canDelete);

    /// @brief writes the packet size and id to the beginning of buffer
    void WriteHeaders();
    /// @brief Sets the position to the buffer at index 0 to start reading size and id
    void PrepareWrite();
    /// @brief Sets the buffer index to the 5th byte to prepare for appending data
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
    uint32_t GetBufferPos() const noexcept{return m_Pos;}
    uint8_t* GetData() const noexcept{return m_Data;}
    uint32_t GetSize() const noexcept{return m_Size;}
    bool CanDeleteData() const noexcept{return m_CanFree;}
private:
    uint8_t* m_Data = nullptr;
    bool m_CanFree = false;
    uint32_t m_Size = 0;

    /// @brief the position at which we read/write at
    uint32_t m_Pos = 0;

    /// @brief and Id that specifies what kind of packet it is
    uint8_t m_Id;
};