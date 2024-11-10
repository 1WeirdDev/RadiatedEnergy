#pragma once

#include "Client.h"

class GameServer{
public:
    GameServer();
    /// @brief Attempts to start a game server on a specified port
    /// @return returns 0 if successful
    int Start(uint16_t port);
    void Stop();
private:
    void StartAccept();

public:
    bool ShouldRun() const noexcept{return m_ShouldRun;}
private:
    asio::io_context m_IOContext;
    tcp::acceptor m_TCPAcceptor;

    std::thread m_RunThread;
    bool m_ShouldRun = false;
    std::vector<std::shared_ptr<Client>> m_Clients;
};