#pragma once

#include "Core.h"
#include "Shared.h"
#include "Packet.h"

class GameServer;
class Client : public std::enable_shared_from_this<Client>{
public:
    Client(GameServer& server, tcp::socket tcpSocket);

    void Start();
    void Disconnect();

    void SendPacket(Packet& packet);
    void SendPacket(Packet&& packet);

    void FreeData();
private:
    void StartTCPAsyncRead();
    void StartTCPAsyncWrite();
    void OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred);
    void OnTCPAsyncWrite(const std::error_code& ec, size_t bytesTransferred);
private:
    GameServer& m_Server;
    tcp::socket m_TCPSocket;
    udp::socket m_UDPSocket;

    Packet m_ReceivePacket;
    std::array<char, CLIENT_MAX_READ_BUFFER_SIZE> m_TCPReadBuffer;
    std::vector<Packet> m_PacketsToWrite;
    bool m_IsWritingTCPPacket=false;
};