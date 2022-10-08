#include "Time.h"

// ��� ���� �ʱ�ȭ
unique_ptr<Time> Time::instance_ = nullptr;
once_flag Time::flag_;

Time* Time::GetInstance()
{
    call_once(flag_, [] // ���ٽ�
        {
            instance_.reset(new Time);
        });

    return instance_.get();
}

void Time::Initiate()
{
    QueryPerformanceFrequency(&second_);
    QueryPerformanceCounter(&time_);

    time_scale_ = 1.0f;
}

void Time::Update()
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);

    delta_time_ = (time.QuadPart - time_.QuadPart) / (float)second_.QuadPart;

    time_ = time;
}

float Time::GetDeltaTime()
{
    return delta_time_ * time_scale_;
}
