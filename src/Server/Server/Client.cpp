#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"
#include "GameServer.h"

Client::Client(GameServer& server, tcp::socket tcpSocket) :
m_Server(server),
m_TCPSocket(std::move(tcpSocket)),
m_UDPSocket(server.GetIOContext()){
}

void Client::Start(){
    StartTCPAsyncRead();
    CORE_DEBUG("Starting Client");
}
void Client::Disconnect(){
    CORE_DEBUG("Disconnecting Client");

    std::error_code ec;
    m_TCPSocket.shutdown(m_TCPSocket.shutdown_both, ec);
    m_UDPSocket.shutdown(m_TCPSocket.shutdown_both, ec);

    m_TCPSocket.cancel(ec);
    m_UDPSocket.cancel(ec);

    m_TCPSocket.close(ec);
    m_UDPSocket.close(ec);
    m_Server.RemoveClient(*this);
    CORE_DEBUG("Disconnected Client");
}
void Client::StartTCPAsyncRead(){
    auto self = shared_from_this();
    m_TCPSocket.async_read_some(asio::buffer(m_TCPReadBuffer, CLIENT_MAX_READ_BUFFER_SIZE), [self](const std::error_code& ec, size_t bytesTransferred){
        self->OnTCPAsyncRead(ec, bytesTransferred);
    });
}
void Client::OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred){
    if(ec){
        Disconnect();
        return;
    }
    CORE_DEBUG("READ {0} bytes.", bytesTransferred);
    StartTCPAsyncRead();
}