#include "pch.h"
#include "Time.h"

std::chrono::high_resolution_clock::time_point Time::s_FrameStart;
std::chrono::high_resolution_clock::time_point Time::s_LastFrameStart;
double Time::s_DeltaTime;

void Time::Init(){
    s_FrameStart = std::chrono::steady_clock::now();
    s_LastFrameStart = std::chrono::steady_clock::now();
    s_DeltaTime = 0.0001f;
}
void Time::Shutdown(){}
void Time::Update(){
    s_FrameStart = std::chrono::steady_clock::now();
    s_DeltaTime = (float)((s_FrameStart - s_LastFrameStart).count() / 1000000000.0);
    s_LastFrameStart = s_FrameStart;
}