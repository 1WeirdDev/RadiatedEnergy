#pragma once

#include "pch.h"

class Mouse{
public:
    static void Init();
    static void Shutdown();

    static void Update();

    static void OnLostFocus();
public:
    static double GetMouseX() noexcept{return s_MousePosX;}
    static double GetMouseY() noexcept{return s_MousePosY;}
    static double GetDeltaX() noexcept{return s_DeltaX;}
    static double GetDeltaY() noexcept{return s_DeltaY;}
    static double GetNormalizedMouseX() noexcept{return s_NormalizedMousePosX;}
    static double GetNormalizedMouseY() noexcept{return s_NormalizedMousePosY;}
private:
    static double s_MousePosX;
    static double s_MousePosY;
    static double s_LastMousePosX;
    static double s_LastMousePosY;
    static double s_NormalizedMousePosX;
    static double s_NormalizedMousePosY;
    static double s_DeltaX;
    static double s_DeltaY;
    static std::array<char, 12> s_Buttons;
    static std::vector<char> s_ButtonsToSet;
};