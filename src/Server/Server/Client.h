#pragma once

#include "Core/Core.h"
#include "Shared.h"

class GameServer;
class Client : public std::enable_shared_from_this<Client>{
public:
    Client(GameServer& server, tcp::socket tcpSocket);

    void Start();
    void Disconnect();
private:
    void StartTCPAsyncRead();
    void OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred);
private:
    GameServer& m_Server;
    tcp::socket m_TCPSocket;
    udp::socket m_UDPSocket;

    std::array<char, CLIENT_MAX_READ_BUFFER_SIZE> m_TCPReadBuffer;
};