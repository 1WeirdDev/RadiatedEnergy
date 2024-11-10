#pragma once

#include "pch.h"

enum class KeyModifierBit{
    None=0,
    Shift=(1<<1),
    Control=(1<<2),
    Alt=(1<<3),
    CapsLock=(1<<4),
};

enum class KeyState{
    Released=0,
    Repeated,
    Pressed
};

class Keyboard{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    
    static bool IsKeyPressed(uint16_t key) noexcept;
    static bool IsKeyDown(uint16_t key) noexcept;
private:
    static std::array<uint8_t, 500> s_Keys;
    static std::vector<uint16_t> s_KeysToSet;
};