#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"

Client::Client(tcp::socket tcpSocket) :
m_TCPSocket(std::move(tcpSocket)){
    StartAsyncRead();
}

void Client::Start(){
    CORE_DEBUG("Starting Client");
}
void Client::StartTCPAsyncRead(){
    auto self = shared_from_this();
    m_TCPSocket->async_read_some(m_TCPReadBuffer, [self](const std::error_code& ec, size_t bytesTransferred){
        self->OnTCPAsyncRead(ec, bytesTransferred);
    });
}
void Client::OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred){
    if(ec){
        Disconnect();
        return;
    }
    CORE_DEBUG("READ {0} bytes.", bytesTransferred);
    self->StartTCPAsyncRead();
}