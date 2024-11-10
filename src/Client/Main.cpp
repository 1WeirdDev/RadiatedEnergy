#include "pch.h"
#include "Game.h"

#include "Rendering/Window.h"

int main(int argc, char** argv){
    Game::Init();
    while(Window::ShouldUpdate()){
        Game::Update();
        Game::Draw();
    }

    Game::Shutdown();
}