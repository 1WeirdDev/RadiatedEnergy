#include "pch.h"
#include "Game.h"

#include "Core/Logger.h"
#include "Display/Window.h"

std::shared_ptr<Client> Game::s_Client;

void Game::Init(){
    Logger::Init();
    Window::Create();

    s_Client = std::make_shared<Client>();
    s_Client->Start();
    s_Client->Connect("127.0.0.1", 8888);
}
void Game::Shutdown(){
    s_Client->Stop();
    Window::Shutdown();
}

void Game::Update(){}
void Game::Draw(){
    
    Window::Update();
}