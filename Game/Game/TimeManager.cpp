#include "pch.h"
#include "TimeManager.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<TimeManager> TimeManager::instance_ = nullptr;
once_flag TimeManager::flag_;

TimeManager::TimeManager() : frequency_{}, previous_count_{}, current_count_{}, delta_time_(), time_scale_(1.f), timer_(), fps_(), counter_()
{
}

shared_ptr<TimeManager> TimeManager::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new TimeManager);
        });

    return instance_;
}

void TimeManager::Release()
{
    instance_.reset();
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

    counter_++;

    previous_count_ = current_count_;

    timer_ += delta_time_;

    if (timer_ >= 1)
    {
        system("cls");

        fps_ = counter_;

        WCHAR word[1024];
        wsprintf(word, L"FPS: %d\n", fps_);
        OutputDebugString(word);

        timer_ = 0;
        counter_ = 0;
    }
}

float TimeManager::GetDeltaTime()
{
    return delta_time_ * time_scale_;
}

UINT TimeManager::GetFPS()
{
    return fps_;
}
