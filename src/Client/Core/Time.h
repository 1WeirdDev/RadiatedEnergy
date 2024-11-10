#pragma once


class Time{
public:
    static void Init();
    static void Shutdown();

    static void Update();

    static double GetDeltaTime() noexcept{return s_DeltaTime;}
private:
    static double s_FrameStartTime;
    static double s_LastFrameStartTime;
    static double s_DeltaTime;
};