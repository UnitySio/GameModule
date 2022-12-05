#include "pch.h"
#include "Camera.h"
#include "Object.h"
#include "Window.h"

using namespace std;

Camera::Camera() :
    position_{},
    screen_position_{},
    resolution_{},
    limit_area_{},
    screen_x_(.5f),
    screen_y_(.5f),
    move_speed_(1.f),
    target_()
{
}

void Camera::Initiate()
{
    resolution_ = WINDOW->GetResolution();
    limit_area_ = {0, 0, resolution_.x_, resolution_.y_};
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

        float clamp_x = clamp(position_.x_, limit_area_.left + (resolution_.x_ * screen_x_),
                              limit_area_.right - (resolution_.x_ - (resolution_.x_ * screen_x_)));
        float clamp_y = clamp(position_.y_, limit_area_.top + (resolution_.y_ * screen_y_),
                              limit_area_.bottom - (resolution_.y_ - (resolution_.y_ * screen_y_)));

        position_ = {clamp_x, clamp_y};

        screen_position_ = position_ - Vector2({resolution_.x_ * screen_x_, resolution_.y_ * screen_y_});
    }
}

void Camera::SetTarget(shared_ptr<Object> target)
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
