#include "pch.h"
#include "TimeManager.h"

using namespace std;

// ��� ���� �ʱ�ȭ
unique_ptr<TimeManager> TimeManager::instance_ = nullptr;
once_flag TimeManager::flag_;

TimeManager::TimeManager() : frequency_{}, previous_count_{}, current_count_{}, delta_time_(), time_scale_(1.f), timer_(), fps_(), counter_()
{
}

TimeManager* TimeManager::GetInstance()
{
    call_once(flag_, [] // ���ٽ�
        {
            instance_.reset(new TimeManager);
        });

    return instance_.get();
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

    if (timer_ > 1.f)
    {
        fps_ = counter_;

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
