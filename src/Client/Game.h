#pragma once

#include "Networking/Client.h"

class Game{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    static void Draw();
public:
    static std::shared_ptr<Client>& GetClient() noexcept{return s_Client;}
private:
    static std::shared_ptr<Client> s_Client;
};