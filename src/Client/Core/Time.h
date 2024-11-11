#pragma once

class Time{
public:
    static void Init();
    static void Shutdown();

    static void Update();

    static double GetDeltaTime() noexcept{return s_DeltaTime;}
private:
    static std::chrono::high_resolution_clock::time_point s_FrameStart;
    static std::chrono::high_resolution_clock::time_point s_LastFrameStart;
    static double s_DeltaTime;
};