#pragma once

#include "Core/Core.h"

#define CLIENT_MAX_READ_BUFFER_SIZE 0xFFFF
class Client : public std::enable_shared_from_this<Client>{
public:
    Client(tcp::socket tcpSocket);

    void Start();
private:
    void StartTCPAsyncRead();
    void OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred);
private:
    tcp::socket m_TCPSocket;
    udp::socket m_UDPSocket;

    std::array<char, CLIENT_MAX_READ_BUFFER_SIZE> m_TCPReadBuffer;
};