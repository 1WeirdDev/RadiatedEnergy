#include "pch.h"
#include "Display/Window.h"

int main(int argc, char** argv){
    Window::Create();

    while(Window::ShouldBeOpen()){
        Window::Update();
    }
    Window::Shutdown();
}