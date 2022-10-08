#pragma once

#include "framework.h"

class Time
{
private:
	// ΩÃ±€≈Ê
	static unique_ptr<Time> instance_;
	static once_flag flag_;

	LARGE_INTEGER second_;
	LARGE_INTEGER time_;

	float delta_time_;
	float time_scale_;
public:
	Time() = default;
	~Time() = default;

	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static Time* GetInstance();

	void Initiate();
	void Update();

	float GetDeltaTime();
};

