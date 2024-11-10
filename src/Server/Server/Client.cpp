#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"

Client::Client(tcp::socket socket) :
m_TCPSocket(std::move(socket)){
    StartAsyncRead();
}

void Client::Start(){
    CORE_DEBUG("Starting Client");
}