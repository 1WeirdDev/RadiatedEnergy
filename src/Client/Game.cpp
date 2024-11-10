#include "pch.h"
#include "Game.h"

#include "Core/Logger.h"
#include "Rendering/Window.h"
#include "Input/Mouse.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes/MainMenuScene.h"

std::shared_ptr<Client> Game::s_Client;

void Game::Init(){
    Logger::Init();
    Window::Create();
    Keyboard::Init();
    Mouse::Init();

    SceneManager::MakeScene<MainMenuScene>(LoadSceneMode::Single);
    s_Client = std::make_shared<Client>();
    s_Client->Start();
    s_Client->Connect("127.0.0.1", 8888);
}
void Game::Shutdown(){
    s_Client->Stop();
    SceneManager::Shutdown();
    Keyboard::Shutdown();
    Window::Destroy();
}

void Game::Update(){
    SceneManager::Update();
    Keyboard::Update();
    Mouse::Update();
}
void Game::Draw(){
    SceneManager::Draw();
    Window::Update();
}

void Game::OnKeyEvent(KeyState state, uint8_t modifiers, uint16_t key){
    SceneManager::HandleKeyEvent(state, modifiers, key);
    //CORE_DEBUG("Key {0} pressed. State {1} modifiers {2}", key, (uint8_t)state, modifiers);
}

void Game::OnMouseButtonEvent(bool isDown, uint8_t key){
}
void Game::OnWindowFocusCallback(bool focused){
    if(!focused)return;
    Keyboard::OnLostFocus();
    Mouse::OnLostFocus();
}

void Game::OnWindowResizeEvent(int width, int height){}
void Game::OnWindowPosCallback(int xPos, int yPos){}