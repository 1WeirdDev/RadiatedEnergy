#pragma once

enum class ServerToClientIds{
None=0,

/// @brief Connected has a uint16_t following for the port
Connected,
UDPConnected,
};