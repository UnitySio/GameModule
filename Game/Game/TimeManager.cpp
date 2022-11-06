#include "pch.h"
#include "TimeManager.h"
#include "Window.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<TimeManager> TimeManager::instance_ = nullptr;
once_flag TimeManager::flag_;

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

std::shared_ptr<TimeManager> TimeManager::GetInstance()
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

	previous_count_ = current_count_;

	frame_counter_++;

	timer_ += delta_time_;

	if (timer_ >= 1.f)
	{
		fps_ = frame_counter_;

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
