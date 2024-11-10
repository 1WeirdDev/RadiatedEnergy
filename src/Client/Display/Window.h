#pragma once

#include "pch.h"

class Window{
public:
    static void Create();
    static void Shutdown();

    static void Update();
public:
    static bool ShouldBeOpen() noexcept{return s_ShouldBeOpen;}
    static GLFWwindow* GetWindow() noexcept{return s_Window;}
private:
    static GLFWwindow* s_Window;
    static bool s_ShouldBeOpen;
};