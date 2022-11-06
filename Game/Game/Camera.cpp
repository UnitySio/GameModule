#include "pch.h"
#include "Camera.h"
#include "Object.h"
#include "Window.h"

#include <random>

using namespace std;

// ��� ���� �ʱ�ȭ
shared_ptr<Camera> Camera::instance_ = nullptr;
once_flag Camera::flag_;

Camera::Camera() :
	position_{},
	screen_position_{},
	resolution_{},
	screen_center_{},
	limit_area_{},
	screen_x_(.5f),
	screen_y_(.5f),
	move_speed_(1.f),
	target_()
{
}

shared_ptr<Camera> Camera::GetInstance()
{
	call_once(flag_, [] // ���ٽ�
		{
			instance_.reset(new Camera);
		});

	return instance_;
}

void Camera::Release()
{
	instance_.reset();
}

void Camera::Initiate()
{
	resolution_ = WINDOW->GetResolution();
	screen_center_ = resolution_ / 2.f;
	limit_area_ = { 0, 0, resolution_.x_, resolution_.y_ };
}

void Camera::Update()
{
}

void Camera::LateUpdate()
{
	if (target_)
	{
		screen_x_ = clamp(screen_x_, 0.f, 1.f);
		screen_y_ = clamp(screen_y_, 0.f, 1.f);

		position_ = Vector2().Lerp(position_, target_->GetPosition(), DELTA_TIME * move_speed_);

		float clamp_x = clamp(position_.x_, limit_area_.left + screen_center_.x_, limit_area_.right - screen_center_.x_);
		float clamp_y = clamp(position_.y_, limit_area_.top + screen_center_.y_, limit_area_.bottom - screen_center_.y_);

		position_ = { clamp_x, clamp_y };

		screen_position_ = position_ - Vector2({ resolution_.x_ * screen_x_, resolution_.y_ * screen_y_ });
	}
}

void Camera::SetTarget(Object* target)
{
	target_ = target;
}

void Camera::SetScreenX(float x)
{
	screen_x_ = x;
}

void Camera::SetScreenY(float y)
{
	screen_y_ = y;
}

void Camera::SetMoveSpeed(float move_speed)
{
	move_speed_ = move_speed;
}

void Camera::SetLimitArea(FloatRect limit_area)
{
	limit_area_ = limit_area;
}

Vector2 Camera::GetRenderPosition(Vector2 position)
{
	return position - screen_position_;
}