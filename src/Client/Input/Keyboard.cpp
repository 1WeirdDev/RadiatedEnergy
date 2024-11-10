#include "pch.h"
#include "Game.h"
#include "Display/Window.h"
#include "Core/Logger.h"

std::array<char, 500> Keyboard::s_Keys;

//TODO: Maybe have keys be some sort of custom keycode instead of glfw
void Keyboard::Init(){
    glfwSetKeyCallback(Window::GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods){
        if(key < 0 || key >= 500)return;

        KeyPressState state;
        switch(action){
        case GLFW_PRESS:
            state = KeyPressState::Pressed;
            break;
        case GLFW_RELEASE:
            state = KeyPressState::Released;
            break;
        case GLFW_REPEAT:
            state = KeyPressState::Repeated;
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