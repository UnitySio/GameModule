#pragma once

#include <Windows.h>

class Time
{
private:
	// ΩÃ±€≈Ê
	static std::unique_ptr<Time> instance_;
	static std::once_flag flag_;

	LARGE_INTEGER frequency_;
	LARGE_INTEGER previous_count_;
	LARGE_INTEGER current_count_;

	float delta_time_;
	float time_scale_;

	float timer_;

	UINT fps_;
	UINT counter_;
public:
	Time();
	~Time() = default;

	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static Time* GetInstance();

	void Initiate();
	void Update();

	float GetDeltaTime();
	UINT GetFPS();
};

