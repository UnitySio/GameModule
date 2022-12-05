#pragma once

#include "Singleton.h"

class Object;

class Camera :
    public Singleton<Camera>
{
private:
    Vector2 position_;
    Vector2 screen_position_;
    Vector2 resolution_;

    FloatRect limit_area_;

    float screen_x_;
    float screen_y_;
    float move_speed_;

    std::shared_ptr<Object> target_;
public:
    Camera();
    ~Camera() final = default;

    void Initiate();
    void Update();
    void LateUpdate();
    void SetTarget(std::shared_ptr<Object> target);
    void SetScreenX(float x);
    void SetScreenY(float y);
    void SetMoveSpeed(float move_speed);
    void SetLimitArea(FloatRect limit_area);

    Vector2 GetRenderPosition(Vector2 position);
};
