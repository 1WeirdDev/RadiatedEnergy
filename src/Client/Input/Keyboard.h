#pragma once

#include "pch.h"

enum class KeyModifierBit{
    None=0,
    Shift=(1<<1),
    Control=(1<<2),
    Alt=(1<<3),
    CapsLock=(1<<4),
};

enum class KeyPressState{
    Pressed=0,
    Released=1,
    Repeated=2
};

class Keyboard{
public:
    static void Init();
    static void Shutdown();

private:
    static std::array<char, 500> s_Keys;
};