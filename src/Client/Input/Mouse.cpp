#include "pch.h"
#include "Mouse.h"
#include "Rendering/Window.h"
#include "Game.h"

double Mouse::s_MousePosX = 0;
double Mouse::s_MousePosY = 0;
double Mouse::s_LastMousePosX = 0;
double Mouse::s_LastMousePosY = 0;
double Mouse::s_NormalizedMousePosX = 0;
double Mouse::s_NormalizedMousePosY = 0;
double Mouse::s_DeltaX = 0;
double Mouse::s_DeltaY = 0;

std::array<char, 12> Mouse::s_Buttons;
std::vector<char> Mouse::s_ButtonsToSet;

void Mouse::Init(){
    s_Buttons.fill(0);

    glfwSetMouseButtonCallback(Window::GetWindow(), [](GLFWwindow* window, int button, int action, int mods){
        if(button < 0 || button >= 12)return;

        Game::OnMouseButtonEvent(action == GLFW_PRESS, button);
        s_ButtonsToSet.push_back(button);
    });
    
    glfwSetCursorPosCallback(Window::GetWindow(), [](GLFWwindow* window, double xpos, double ypos){
        s_MousePosX = xpos;
        s_MousePosY = ypos;
        s_DeltaX = s_MousePosX - s_LastMousePosX;
        s_DeltaY = s_MousePosY - s_LastMousePosY;
        s_LastMousePosX = s_MousePosX;
        s_LastMousePosY = s_MousePosY;
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
    s_DeltaX = 0;
    s_DeltaY = 0;
}
void Mouse::OnLostFocus(){
    s_Buttons.fill(0);
    s_ButtonsToSet.resize(0);
}