#pragma once

#include "pch.h"

#define LOGGER_NAME "Client"
#define GAME_NAME "RadiatedEnergy"

#ifdef DIST
#define MESSAGE_BOX(title, message)
#else
#define MESSAGE_BOX(title, message) MessageBoxW(NULL, L##message, L##title, MB_ICONERROR | MB_YESNO);  
#endif

using tcp = asio::ip::tcp;
using udp = asio::ip::udp;