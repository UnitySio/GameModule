#include "pch.h"
#include "Time.h"

using namespace std;

// 멤버 변수 초기화
unique_ptr<Time> Time::instance_ = nullptr;
once_flag Time::flag_;

Time::Time() : frequency_{}, previous_count_{}, current_count_{}, delta_time_(), time_scale_(1.f), timer_(), fps_(), counter_()
{
}

Time* Time::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new Time);
        });

    return instance_.get();
}

void Time::Initiate()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previous_count_);
}

void Time::Update()
{
    QueryPerformanceCounter(&current_count_);

    delta_time_ = (current_count_.QuadPart - previous_count_.QuadPart) / (float)frequency_.QuadPart;

    counter_++;

    previous_count_ = current_count_;

    timer_ += delta_time_;

    if (timer_ > 1.f)
    {
        fps_ = counter_;

        timer_ = 0;
        counter_ = 0;
    }
}

float Time::GetDeltaTime()
{
    return delta_time_ * time_scale_;
}

UINT Time::GetFPS()
{
    return fps_;
}
