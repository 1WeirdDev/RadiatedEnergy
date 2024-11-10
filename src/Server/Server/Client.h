#pragma once

#include "Core/Core.h"

class Client : public std::enable_shared_from_this<Client>{
public:
    Client(tcp::socket socket);

    void Start();
private:
    tcp::socket m_TCPSocket;
};