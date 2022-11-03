#pragma once

class Object;

class Camera
{
private:
	// ΩÃ±€≈Ê
	static std::shared_ptr<Camera> instance_;
	static std::once_flag flag_;

	Vector2 position_;
	Vector2 distance_;

	Object* target_;
public:
	Camera();
	~Camera() = default;

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static std::shared_ptr<Camera> GetInstance();

	void Release();
	void LateUpdate();
	void SetTarget(Object* target);

	Vector2 GetRenderPosition(Vector2 position);
};

