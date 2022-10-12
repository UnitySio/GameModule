#pragma once

#include <Windows.h>

class TimeManager
{
private:
	// ΩÃ±€≈Ê
	static std::unique_ptr<TimeManager> instance_;
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
	TimeManager();
	~TimeManager() = default;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;

	static TimeManager* GetInstance();

	void Initiate();
	void Update();

	float GetDeltaTime();
	UINT GetFPS();
};

