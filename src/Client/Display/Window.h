#pragma once

#include "pch.h"

class Window{
public:
    static void Create();
    static void Shutdown();

    static void Update();

    /// @brief Centers the window in the middle of the screen
    static void Center();
public:
    static bool ShouldBeOpen() noexcept{return s_ShouldBeOpen;}
    static GLFWwindow* GetWindow() noexcept{return s_Window;}
private:
    static GLFWwindow* s_Window;
    static int s_Width;
    static int s_Height;
    static bool s_ShouldBeOpen;
};