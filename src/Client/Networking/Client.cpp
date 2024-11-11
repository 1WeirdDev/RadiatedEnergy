#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"

Client::Client() :
m_TCPSocket(m_IOContext),
m_UDPSocket(m_IOContext),
m_TCPResolver(m_IOContext),
m_UDPResolver(m_IOContext),
m_ReceivePacket((uint8_t*)m_TCPReadBuffer, CLIENT_MAX_READ_BUFFER_SIZE, false){}

Client::~Client(){
    Disconnect();
}
void Client::Start(){
    m_ShouldRun = true;
    auto self = shared_from_this();
    m_RunThread = std::thread([self](){
        while(self->m_ShouldRun){
            self->m_IOContext.poll_one();
        }
    });
}

void Client::Stop(){
    Disconnect();
    m_ShouldRun = false;
    if(m_RunThread.joinable())
        m_RunThread.join();
    m_IsSendingTCPPacket = false;
    m_IsConnected = false;
    m_IsAttemptingConnect = false;
}
void Client::Connect(std::string hostName, uint16_t port){
    Disconnect();

    auto self = shared_from_this();
    m_IsConnected = false;
    m_IsAttemptingConnect = true;

    m_TCPResolver.async_resolve(hostName, std::to_string(port), [self, this, hostName, port](
    const asio::error_code& ec,
    tcp::resolver::results_type results){
        if(ec){
            CORE_ERROR("Failed resolving {0}:{1}, {3}", hostName, port, ec.message());
            self->Disconnect();
            return;
        }
        self->m_TCPSocket.async_connect(*results.begin(), [self, this, hostName, port](const std::error_code& ec){
            if(ec){
                CORE_ERROR("Failed connecting to {0}:{1}, {2}", hostName, port, ec.message());
                self->Disconnect();
                return;
            }
            m_IsConnected = true;
            m_IsAttemptingConnect = false;
            StartTCPAsyncRead();
        });
    });
}

void Client::Disconnect(){
    if(!m_IsAttemptingConnect && !m_IsConnected)return;
    CORE_INFO("Disconnecting from server");
    std::error_code ec;
    
    m_TCPSocket.shutdown(m_TCPSocket.shutdown_both, ec);
    m_UDPSocket.shutdown(m_UDPSocket.shutdown_both, ec);

    m_TCPSocket.cancel(ec); 
    m_UDPSocket.cancel(ec);

    m_TCPSocket.close(ec);
    m_UDPSocket.close(ec);

    m_IsConnected = false;
    m_IsAttemptingConnect = false;
    
    CORE_INFO("Disconnected from server");
}
void Client::SendTCPPacket(Packet&& packet){
    packet.WriteHeaders();
    m_TCPPacketsToSend.emplace_back(std::move(packet));
    StartTCPAsyncWrite();
}

void Client::SetPacketReceivedCallback(ClientPacketCallback callback){
    m_PacketReceivedCallback = callback;
}
void Client::StartTCPAsyncRead(){
    auto self = shared_from_this();
    m_TCPSocket.async_read_some(asio::buffer(m_TCPReadBuffer, CLIENT_MAX_READ_BUFFER_SIZE), [self](const std::error_code& ec, size_t bytesTransferred){
        if(ec){
            CORE_ERROR("Error reading from server : {0}", ec.message());
            self->Disconnect();
            return;
        }

        //TODO: handle packets split
        CORE_INFO("Read {0} bytes", bytesTransferred);
        self->m_ReceivePacket.SetBuffer((uint8_t*)self->m_TCPReadBuffer, bytesTransferred, false);
        
        CORE_INFO("T1");
        self->m_ReceivePacket.PrepareRead();
        CORE_INFO("T2");
        if(self->m_PacketReceivedCallback)
            self->m_PacketReceivedCallback(self->m_ReceivePacket);
        CORE_INFO("T3");
        self->StartTCPAsyncRead();
    });
}
void Client::StartTCPAsyncWrite(){
    if(!m_IsConnected || m_IsSendingTCPPacket)return;
    if(m_TCPPacketsToSend.size() < 1)return;

    auto self = shared_from_this();
    m_IsSendingTCPPacket = true;

    Packet& packet = m_TCPPacketsToSend[0];
    m_TCPSocket.async_write_some(asio::buffer(packet.GetData(), packet.GetBufferPos()), [self, this](const std::error_code& ec, size_t bytesTransferred){
        if(ec){
            CORE_ERROR("Error reading from server : {0}", ec.message());
            self->Disconnect();
            return;
        }

        //TODO: handle packets split
        CORE_INFO("Transferred {0} bytes", bytesTransferred);
        self->m_ReceivePacket.SetBuffer((uint8_t*)self->m_TCPReadBuffer, bytesTransferred, false);

        self->m_ReceivePacket.PrepareRead();

        if(self->m_PacketReceivedCallback)
            self->m_PacketReceivedCallback(self->m_ReceivePacket);

        m_TCPPacketsToSend[0].Free();
        m_TCPPacketsToSend.erase(m_TCPPacketsToSend.begin());
        m_IsSendingTCPPacket = false;
        self->StartTCPAsyncWrite();
    });
}