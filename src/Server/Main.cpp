#include "pch.h"

#include "Core/Logger.h"
#include "Server/GameServer.h"

int main(int argc, char** argv){
    Logger::Init();

    GameServer server;

    server.Start(8888);

    while(server.ShouldRun()){
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command); // Use getline for strings to handle spaces

        if(command == "stop"){
            server.Stop();
            break;
        }

        if(command == "help"){
            CORE_INFO("\"stop\" - stops the server and closes the program");
            continue;
        }

        if(command.size() < 1)continue;

        CORE_ERROR("'{0}' is not recognized as a command", command);
    }
    
    server.Stop();
}