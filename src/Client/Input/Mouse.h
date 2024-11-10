#pragma once

#include "pch.h"

class Mouse{
public:
    static void Init();
    static void Shutdown();

    static void Update();
private:
    static std::array<char, 12> s_Buttons;
    static std::vector<char> s_ButtonsToSet;
};