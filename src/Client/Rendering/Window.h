#pragma once

#include "pch.h"
#include "Core.h"

//All the data we directly give to the window
struct WindowData{
    int m_X = 0;
    int m_Y = 0;
    int m_Width = 1280;
    int m_Height = 720;
    const char* m_Title = GAME_NAME;
    bool m_VsyncEnabled = false;
};

class Window{
public:
    static void Create();
    static void Destroy();

    static void Update();

    static void Close();
    static bool ShouldUpdate() noexcept;

    static void SetBackgroundColor(float r, float g, float b);

    static int GetWidth() noexcept {return s_Data.m_Width;}
    static int GetHeight() noexcept {return s_Data.m_Height;}
    static const char* GetTitle() noexcept {return s_Data.m_Title;}

    static float GetAspectRatio() noexcept {return s_AspectRatio;}
    static float GetInverseAspectRatio() noexcept {return s_InverseAspectRatio;}

    static float GetPixelSizeX() noexcept{return s_PixelSizeX;}
    static float GetPixelSizeY() noexcept{return s_PixelSizeY;}

    static GLFWwindow* GetWindow() noexcept{return s_Window;}
private:
    static WindowData s_Data;
    static bool s_ShouldUpdate;
    //These get calculated off the data
    static float s_AspectRatio;
    static float s_InverseAspectRatio;
    static float s_PixelSizeX;
    static float s_PixelSizeY;
    
    static GLFWwindow* s_Window;
};