#pragma once

#include "Singleton.h"

class TimeManager :
	public Singleton<TimeManager>
{
private:
	LARGE_INTEGER frequency_;
	LARGE_INTEGER previous_count_;
	LARGE_INTEGER current_count_;

	float delta_time_;
	float time_scale_;
	float timer_;

	UINT fps_;
	UINT frame_counter_;
public:
	TimeManager();
	~TimeManager() final = default;

	void Initiate();
	void Update();
	void SetTimeScale(float value);

	float GetDeltaTime();
	float GetTimeScale();
	UINT GetFPS();
};
