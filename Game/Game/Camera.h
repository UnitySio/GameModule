#pragma once

class Object;

class Camera
{
private:
	// �̱���
	static std::shared_ptr<Camera> instance_;
	static std::once_flag flag_;

	Vector2 position_;
	Vector2 screen_position_;
	Vector2 resolution_;
	Vector2 screen_center_;

	FloatRect limit_area_;

	float screen_x_;
	float screen_y_;
	float move_speed_;

	Object* target_;
public:
	Camera();
	~Camera() = default;

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static std::shared_ptr<Camera> GetInstance();

	void Release();
	void Initiate();
	void Update();
	void LateUpdate();
	void SetTarget(Object* target);
	void SetScreenX(float x);
	void SetScreenY(float y);
	void SetMoveSpeed(float move_speed);
	void SetLimitArea(FloatRect limit_area);

	Vector2 GetRenderPosition(Vector2 position);
};
