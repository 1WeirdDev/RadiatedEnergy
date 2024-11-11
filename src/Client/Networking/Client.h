#pragma once

#include "Core.h"
#include "Shared.h"
#include "Packet.h"

typedef std::function<void(Packet& packet)> ClientPacketCallback;
class Client : public std::enable_shared_from_this<Client>{
public:
    Client();
    ~Client();

    /// @brief Starts a thread that handles iocontext
    void Start();

    /// @brief Disconnects and stops the running thread
    void Stop();

    void Connect(std::string hostName, uint16_t port);
    void Disconnect();

    void SendTCPPacket(Packet&& packet);
public:
    void SetPacketReceivedCallback(ClientPacketCallback callback);
    bool IsAttemptingConnected() const noexcept{return m_IsAttemptingConnect;}
    bool IsConnected() const noexcept{return m_IsConnected;}
    bool ShouldRun() const noexcept{return m_ShouldRun;}
private:
    void StartTCPAsyncRead();
    void StartTCPAsyncWrite();
private:
    asio::io_context m_IOContext;
    std::thread m_RunThread;

    tcp::resolver m_TCPResolver;
    tcp::socket m_TCPSocket;
    char m_TCPReadBuffer[CLIENT_MAX_READ_BUFFER_SIZE];
    std::vector<Packet> m_TCPPacketsToSend;
    bool m_IsSendingTCPPacket = false;

    udp::socket m_UDPSocket;
    udp::resolver m_UDPResolver;

    bool m_IsAttemptingConnect = false;
    bool m_IsConnected = false;
    bool m_ShouldRun = false;

    Packet m_ReceivePacket;
    ClientPacketCallback m_PacketReceivedCallback;

};