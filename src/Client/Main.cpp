#include "pch.h"
#include "Core/Logger.h"
#include "Display/Window.h"

#include "Networking/Client.h"

int main(int argc, char** argv){
    Logger::Init();
    Window::Create();

    std::shared_ptr<Client> client = std::make_shared<Client>();
    client->Start();

    client->Connect("127.0.0.1", 8888);

    while(Window::ShouldBeOpen()){
        Window::Update();
    }

    client->Stop();
    Window::Shutdown();
}