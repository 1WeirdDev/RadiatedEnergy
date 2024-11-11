#include "pch.h"
#include "Client.h"
#include "Core/Logger.h"

Client::Client() :
m_TCPSocket(m_IOContext),
m_UDPSocket(m_IOContext),
m_TCPResolver(m_IOContext),
m_UDPResolver(m_IOContext),
m_ReceivePacket(0){}

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
}
void Client::Connect(std::string hostName, uint16_t port){
    Disconnect();

    auto self = shared_from_this();
    m_IsConnected = false;
    m_IsAttemptingConnect = true;

    m_TCPResolver.async_resolve(hostName, std::to_string(port), [self, hostName, port](
    const asio::error_code& ec,
    tcp::resolver::results_type results){
        if(ec){
            CORE_ERROR("Failed resolving {0}:{1}, {3}", hostName, port, ec.message());
            self->Disconnect();
            return;
        }
        self->m_TCPSocket.async_connect(*results.begin(), [self, hostName, port](const std::error_code& ec){
            if(ec){
                CORE_ERROR("Failed connecting to {0}:{1}, {2}", hostName, port, ec.message());
                self->Disconnect();
                return;
            }
            CORE_INFO("Connected to {0}", hostName);
            self->StartTCPAsyncRead();
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

void Client::SetPacketReceivedCallback(ClientPacketCallback callback){
    m_PacketReceivedCallback = callback;
}
void Client::OnConnect(const std::error_code& ec){
    if(ec){
        Disconnect();
        return;
    }
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
        self->m_ReceivePacket.PrepareRead();
        self->m_ReceivePacket.SetBuffer((uint8_t*)self->m_TCPReadBuffer, bytesTransferred, false);
        self->m_PacketReceivedCallback(self->m_ReceivePacket);
        self->StartTCPAsyncRead();
    });
}