#pragma once

#include "pch.h"

class Window{
public:
    static void Create();
    static void Shutdown();

    static void Update();

    static bool ShouldBeOpen() noexcept{return s_ShouldBeOpen;}

private:
    static GLFWwindow* s_Window;
    static bool s_ShouldBeOpen;
};