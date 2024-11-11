#include "pch.h"
#include "Game.h"

#include "Core/Logger.h"
#include "Core/Time.h"
#include "Rendering/Window.h"
#include "Input/Mouse.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes/MainMenuScene.h"
#include "Rendering/Gui/UIDisplayManager.h"
#include "Packet.h"

std::shared_ptr<Client> Game::s_Client;

void Game::Init(){
    Logger::Init();
    Window::Create();
    UIDisplayManager::Init();
    Keyboard::Init();
    Mouse::Init();

    Time::Init();

    Packet packet;
    packet.WriteInt16(8012);
    packet.WriteInt32(-1273421);
    packet.WriteUInt32(782314);
    packet.WriteString("HELLO SUSSY BALLS(CAPPED)");

    packet.PrepareRead();
    packet.ReadInt32();
    int16_t f1 = packet.ReadInt16();
    int32_t f2 = packet.ReadInt32();
    uint32_t f3 = packet.ReadUInt32();
    std::string f4 = packet.ReadString();
    CORE_DEBUG("READ {0} {1} {2} {3}", f1, f2, f3, f4);

    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);

    SceneManager::MakeScene<MainMenuScene>(LoadSceneMode::Single);
    s_Client = std::make_shared<Client>();
    s_Client->Start();
    s_Client->Connect("127.0.0.1", 8888);
}
void Game::Shutdown(){
    s_Client->Stop();
    SceneManager::Shutdown();
    Keyboard::Shutdown();
    UIDisplayManager::Shutdown();
    Window::Destroy();
}

void Game::Update(){
    Time::Update();
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