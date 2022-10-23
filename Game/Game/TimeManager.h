#pragma once
class TimeManager
{
private:
	// �̱���
	static std::shared_ptr<TimeManager> instance_;
	static std::once_flag flag_;

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
	~TimeManager() = default;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;

	static std::shared_ptr<TimeManager> GetInstance();

	void Initiate();
	void Release();
	void Update();
	void SetTimeScale(float value);

	float GetDeltaTime();
	float GetTimeScale();
	UINT GetFPS();
};
