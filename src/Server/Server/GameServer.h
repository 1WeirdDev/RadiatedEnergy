#pragma once

#include "Client.h"

typedef std::function<void(Packet&, Client&)> PacketReceivedCallback;
class GameServer{
public:
    friend class Client;
    GameServer();
    /// @brief Attempts to start a game server on a specified port
    /// @return returns 0 if successful
    int Start(uint16_t port);
    void Stop();

    void SetPacketReceivedCallback(PacketReceivedCallback callback);
public:
    const PacketReceivedCallback& GetPacketReceivedCallback() const noexcept{return m_PacketReceivedCallback;}
    asio::io_context& GetIOContext() const noexcept{return (asio::io_context&)m_IOContext;}
    bool ShouldRun() const noexcept{return m_ShouldRun;}
private:
    void StartAccept();

    void RemoveClient(Client& client);
private:
    asio::io_context m_IOContext;
    tcp::acceptor m_TCPAcceptor;

    std::thread m_RunThread;
    bool m_ShouldRun = false;
    std::vector<std::shared_ptr<Client>> m_Clients;

    PacketReceivedCallback m_PacketReceivedCallback;
};