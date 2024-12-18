#pragma once

#include <iostream>
#include <fstream>

#include <map>
#include <unordered_map>

#include <functional>
#include <algorithm>

#include <chrono>
#include <string>

#include <array>
#include <vector>
#include <bitset>

#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#if Platform == Windows
    extern "C" {
    #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
    #define NOMINMAX             // Prevents min/max macros from being defined

    #ifndef UNICODE
    #define UNICODE
    #define UNICODE_WAS_UNDEFINED
    #endif

    #include <Windows.h>
    #undef APIENTRY  // Undefine conflicting macro

    #ifdef UNICODE_WAS_UNDEFINED
    #undef UNICODE
    #endif
}

#else
#error invalid platform
#endif

#define ASIO_STANDALONE
#include <asio.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>