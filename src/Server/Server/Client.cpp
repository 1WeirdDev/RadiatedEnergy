#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"
#include "GameServer.h"

Client::Client(GameServer& server, tcp::socket tcpSocket) :
m_Server(server),
m_TCPSocket(std::move(tcpSocket)),
m_UDPSocket(server.GetIOContext()),
m_ReceivePacket(0),
m_IsConnected(true){
}

void Client::Start(){
    StartTCPAsyncRead();
    CORE_DEBUG("Starting Client");
}
void Client::Disconnect(){
    if(!m_IsConnected)return;

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

    FreeData();
    m_IsConnected = false;
}
void Client::FreeData(){
    for(size_t i = 0; i < m_PacketsToWrite.size(); i++)
        m_PacketsToWrite[i].Free();
    m_PacketsToWrite.resize(0);
}
void Client::SendPacket(Packet& packet){
    packet.WriteHeaders();
    m_PacketsToWrite.emplace_back(packet);
    StartTCPAsyncWrite();
}
void Client::SendPacket(Packet&& packet){
    packet.WriteHeaders();
    m_PacketsToWrite.emplace_back(std::move(packet));
    StartTCPAsyncWrite();
}
void Client::StartTCPAsyncRead(){
    auto self = shared_from_this();
    m_TCPSocket.async_read_some(asio::buffer(m_TCPReadBuffer, CLIENT_MAX_READ_BUFFER_SIZE), [self](const std::error_code& ec, size_t bytesTransferred){
        self->OnTCPAsyncRead(ec, bytesTransferred);
    });
}
void Client::StartTCPAsyncWrite(){
    if(m_IsWritingTCPPacket || !m_IsConnected)return;
    if(m_PacketsToWrite.size() < 1)return;
    m_IsWritingTCPPacket = true;

    auto self = shared_from_this();
    m_TCPSocket.async_write_some(asio::buffer(m_PacketsToWrite[0].GetData(), CLIENT_MAX_READ_BUFFER_SIZE), [self](const std::error_code& ec, size_t bytesTransferred){
        self->OnTCPAsyncWrite(ec, bytesTransferred);
    });
}
void Client::OnTCPAsyncRead(const std::error_code& ec, size_t bytesTransferred){
    if(ec){
        Disconnect();
        return;
    }
    CORE_DEBUG("Received {0} bytes.", bytesTransferred);
    m_ReceivePacket.PrepareRead();
    m_ReceivePacket.SetBuffer((uint8_t*)m_TCPReadBuffer.data(), bytesTransferred, false);
    m_Server.GetPacketReceivedCallback()(m_ReceivePacket, *this);
    StartTCPAsyncRead();
}
void Client::OnTCPAsyncWrite(const std::error_code& ec, size_t bytesTransferred){
    if(ec){
        Disconnect();
        return;
    }
    CORE_DEBUG("Wrote {0} bytes.", bytesTransferred);
    m_PacketsToWrite.erase(m_PacketsToWrite.begin());
    m_IsWritingTCPPacket = false;
    StartTCPAsyncRead();
}