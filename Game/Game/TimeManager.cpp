#include "pch.h"
#include "TimeManager.h"
#include "Window.h"

using namespace std;

TimeManager::TimeManager() :
    frequency_{},
    previous_count_{},
    current_count_{},
    delta_time_(),
    time_scale_(1.f),
    timer_(),
    fps_(),
    frame_counter_()
{
}

void TimeManager::Initiate()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previous_count_);
}

void TimeManager::Update()
{
    QueryPerformanceCounter(&current_count_);

    delta_time_ = (current_count_.QuadPart - previous_count_.QuadPart) / (float)frequency_.QuadPart;

    previous_count_ = current_count_;

    frame_counter_++;

    timer_ += delta_time_;

    if (timer_ >= 1.f)
    {
        fps_ = frame_counter_;

        WCHAR word[1024];
        wsprintf(word, L"FPS: %d\n", fps_);
        OutputDebugString(word);

        frame_counter_ = 0;
        timer_ = 0;
    }
}

void TimeManager::SetTimeScale(float value)
{
    time_scale_ = value;
}

float TimeManager::GetDeltaTime()
{
    return delta_time_ * time_scale_;
}

float TimeManager::GetTimeScale()
{
    return time_scale_;
}

UINT TimeManager::GetFPS()
{
    return fps_;
}
