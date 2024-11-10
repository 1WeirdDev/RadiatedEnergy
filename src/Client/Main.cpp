#include "pch.h"
#include "Game.h"

#include "Display/Window.h"

int main(int argc, char** argv){
    Game::Init();
    while(Window::ShouldBeOpen()){
        Game::Update();
        Game::Draw();
    }

    Game::Shutdown();
}