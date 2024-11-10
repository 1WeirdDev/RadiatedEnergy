#include "pch.h"
#include "Time.h"

double Time::s_FrameStartTime = 0;
double Time::s_LastFrameStartTime = 0;
double Time::s_DeltaTime = 0;

void Time::Init(){
    s_FrameStartTime = 0;
    s_LastFrameStartTime = 0;
    s_DeltaTime = 0;
}
void Time::Shutdown(){}
void Time::Update(){
    s_FrameStartTime = glfwGetTime();
    s_DeltaTime = s_FrameStartTime = s_LastFrameStartTime;
    s_LastFrameStartTime = s_FrameStartTime;
}