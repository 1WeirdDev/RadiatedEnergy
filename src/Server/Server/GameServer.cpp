#include "pch.h"
#include "GameServer.h"
#include "Core/Logger.h"

GameServer::GameServer():
m_TCPAcceptor(m_IOContext),
m_ClientConnectedCallback(nullptr),
m_PacketReceivedCallback(nullptr){}

int GameServer::Start(uint16_t port){
    CORE_INFO("Starting server on port {0}", port);

    tcp::endpoint endpoint(tcp::v4(), port);

    // Open the acceptor on the specified endpoint
    std::error_code ec;
    m_TCPAcceptor.open(endpoint.protocol(), ec);
    if(ec){
        CORE_ERROR("Failed to open ip4 protocol", port);
        return -1;
    }

    // Bind the acceptor to the endpoint
    m_TCPAcceptor.bind(endpoint, ec);
    if(ec){
        CORE_ERROR("Failed to bind to port {0}", port);
        return -1;
    }
    // Start listening for incoming connections
    m_TCPAcceptor.listen(180, ec);

    if(ec){
        CORE_ERROR("Failed to listen on port {0}", port);
        return -1;
    }

    m_ShouldRun = true;
    StartAccept();

    m_RunThread = std::thread([this](){
        while(m_ShouldRun){
            m_IOContext.poll_one();
        }
    });
    CORE_INFO("Started server on port {0}", port);
    return 0;
}

void GameServer::Stop(){
    if(!m_ShouldRun)return;

    m_ShouldRun = false;
    if(m_RunThread.joinable())
        m_RunThread.join();
    
    CORE_INFO("Successfully closed server");
}

void GameServer::SetClientConnectedCallback(ClientConnectedCallback callback){
    m_ClientConnectedCallback = callback;
}
void GameServer::SetPacketReceivedCallback(PacketReceivedCallback callback){
    m_PacketReceivedCallback = callback;
}
void GameServer::StartAccept(){
    m_TCPAcceptor.async_accept([this](const std::error_code& ec, tcp::socket tcpSocket){
        if(ec){
            CORE_ERROR("Failed to accept socket : {0}", ec.message());
            Stop();
            return;
        }

        std::shared_ptr<Client> client = std::make_shared<Client>(*this, std::move(tcpSocket));
        m_Clients.push_back(client);
        m_ClientConnectedCallback(*client);
        client->Start();
        StartAccept();
    });
}

void GameServer::RemoveClient(Client& client){
    CORE_DEBUG("Removing Client");
    for(size_t i = 0; i < m_Clients.size(); i++){
        if(m_Clients[i].get() == &client){
            CORE_DEBUG("Removing");
            m_Clients.erase(m_Clients.begin() + i);
            CORE_DEBUG("Success Removing");
            return;
        }
    }
    CORE_DEBUG("Failed To Remove Client");
}