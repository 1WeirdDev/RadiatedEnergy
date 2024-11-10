#include "pch.h"
#include "Game.h"
#include "Rendering/Window.h"
#include "Core/Logger.h"

std::array<uint8_t, 500> Keyboard::s_Keys;
std::vector<uint16_t> Keyboard::s_KeysToSet;

//TODO: Maybe have keys be some sort of custom keycode instead of glfw
void Keyboard::Init(){
    s_Keys.fill(0);

    glfwSetKeyCallback(Window::GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods){
        if(key < 0 || key >= 500)return;

        KeyState state;
        switch(action){
        case GLFW_PRESS:
            s_Keys[key] = (uint8_t)KeyState::Pressed;
            state = KeyState::Pressed;
            s_KeysToSet.push_back(key);
            break;
        case GLFW_RELEASE:
            s_Keys[key] = (uint8_t)KeyState::Released;
            state = KeyState::Released;
            break;
        case GLFW_REPEAT:
            state = KeyState::Repeated;
            break;
        default:
            return;
        }

        uint8_t modifiers = 0;
        if(mods & GLFW_MOD_SHIFT)modifiers |= (uint8_t)KeyModifierBit::Shift;
        if(mods & GLFW_MOD_ALT)modifiers |= (uint8_t)KeyModifierBit::Alt;
        if(mods & GLFW_MOD_CAPS_LOCK)modifiers |= (uint8_t)KeyModifierBit::CapsLock;
        if(mods & GLFW_MOD_CONTROL)modifiers |= (uint8_t)KeyModifierBit::Control;

        //Key Event
        Game::OnKeyEvent(state, modifiers, key);
    });
    CORE_INFO("Initialized Keyboard");
}
void Keyboard::Shutdown(){
    CORE_INFO("Shutdown Keyboard");
}
void Keyboard::Update(){
    for(size_t i = 0; i < s_KeysToSet.size();i++){
        uint16_t key = s_KeysToSet[i];
        if(s_Keys[key] == (uint8_t)KeyState::Pressed)s_Keys[key] = (uint8_t)KeyState::Repeated;
    }
    s_KeysToSet.resize(0);
}
bool Keyboard::IsKeyPressed(uint16_t key) noexcept{
    if(key < 0 || key >= s_Keys.size())return false;
    return s_Keys[key] == (uint8_t)KeyState::Pressed;
}
bool Keyboard::IsKeyDown(uint16_t key) noexcept{
    if(key < 0 || key >= s_Keys.size())return false;
    return s_Keys[key] != (uint8_t)KeyState::Released;
}
void Keyboard::OnLostFocus(){
    s_Keys.fill(0);
    s_KeysToSet.resize(0);
}