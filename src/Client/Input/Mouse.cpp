#include "pch.h"
#include "Mouse.h"
#include "Rendering/Window.h"
#include "Game.h"

std::array<char, 12> Mouse::s_Buttons;
std::vector<char> Mouse::s_ButtonsToSet;

void Mouse::Init(){
    s_Buttons.fill(0);

    glfwSetMouseButtonCallback(Window::GetWindow(), [](GLFWwindow* window, int button, int action, int mods){
        if(button < 0 || button >= 12)return;

        Game::OnMouseButtonEvent(action == GLFW_PRESS, button);
        s_ButtonsToSet.push_back(button);
    });
}
void Mouse::Shutdown(){

}

void Mouse::Update(){
    for(size_t i = 0; i < s_ButtonsToSet.size(); i++){
        uint8_t button = s_ButtonsToSet[i];
        if(s_Buttons[button])s_Buttons[button] = 1;
    }
    s_ButtonsToSet.resize(0);
}
void Mouse::OnLostFocus(){
    s_Buttons.fill(0);
    s_ButtonsToSet.resize(0);
}