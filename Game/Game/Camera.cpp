#include "pch.h"
#include "Camera.h"
#include "Object.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<Camera> Camera::instance_ = nullptr;
once_flag Camera::flag_;

Camera::Camera() :
	position_{},
	target_()
{
}

shared_ptr<Camera> Camera::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new Camera);
		});

	return instance_;
}

void Camera::Release()
{
	instance_.reset();
}

void Camera::LateUpdate()
{
	if (target_)
	{
		position_ = target_->GetPosition();

		distance_ = position_ - Vector2({ 320.f, 240.f });
	}
}

void Camera::SetTarget(Object* target)
{
	target_ = target;
}

Vector2 Camera::GetRenderPosition(Vector2 position)
{
	return position - distance_;
}
