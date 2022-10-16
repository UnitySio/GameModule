#pragma once

class Object;

class Camera
{
private:
	// ΩÃ±€≈Ê
	static std::shared_ptr<Camera> instance_;
	static std::once_flag flag_;

	std::shared_ptr<Object> follow_;
public:
	Camera();
	~Camera() = default;

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static std::shared_ptr<Camera> GetInstance();

	void Release();
};

