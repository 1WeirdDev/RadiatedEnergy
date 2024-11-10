#pragma once

#include "Networking/Client.h"
#include "Input/Keyboard.h"

class Game{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    static void Draw();

    static void OnKeyEvent(KeyState state, uint8_t modifiers, uint16_t key);
    static void OnMouseButtonEvent(bool isDown, uint8_t key);
    static void OnWindowFocusCallback(bool focused);
    static void OnWindowResizeEvent(int width, int height);
    static void OnWindowPosCallback(int xPos, int yPos);
public:
    static std::shared_ptr<Client>& GetClient() noexcept{return s_Client;}
private:
    static std::shared_ptr<Client> s_Client;
};