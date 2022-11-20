#include "pch.h"
#include "Vector2.h"

using namespace std;

Vector2::Vector2() :
    x_(),
    y_()
{
}

Vector2::Vector2(float x_, float y_)
{
    this->x_ = x_;
    this->y_ = y_;
}

Vector2& Vector2::operator+=(const Vector2& kVector2)
{
    x_ += kVector2.x_;
    y_ += kVector2.y_;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& kVector2)
{
    x_ -= kVector2.x_;
    y_ -= kVector2.y_;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& kVector2)
{
    x_ *= kVector2.x_;
    y_ *= kVector2.y_;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& kVector2)
{
    x_ /= kVector2.x_;
    y_ /= kVector2.y_;
    return *this;
}

Vector2& Vector2::operator=(const Vector2& kVector2)
{
    x_ = kVector2.x_;
    y_ = kVector2.y_;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& kVector2)
{
    return {x_ + kVector2.x_, y_ + kVector2.y_};
}

Vector2 Vector2::operator-(const Vector2& kVector2)
{
    return {x_ - kVector2.x_, y_ - kVector2.y_};
}

Vector2 Vector2::operator*(const Vector2& kVector2)
{
    return {x_ * kVector2.x_, y_ * kVector2.y_};
}

Vector2 Vector2::operator/(const Vector2& kVector2)
{
    return {x_ / kVector2.x_, y_ / kVector2.y_};
}

Vector2 Vector2::operator+(float value)
{
    return {x_ + value, y_ + value};
}

Vector2 Vector2::operator-(float value)
{
    return {x_ - value, y_ - value};
}

Vector2 Vector2::operator*(float value)
{
    return {x_ * value, y_ * value};
}

Vector2 Vector2::operator/(float value)
{
    return {x_ / value, y_ / value};
}

Vector2 Vector2::Normalized()
{
    float m = sqrt(pow(x_, 2) + pow(y_, 2));

    if (m > 0)
    {
        return {x_ /= m, y_ /= m};
    }

    return {0, 0};
}

Vector2 Vector2::Zero()
{
    return Vector2({0, 0});
}

Vector2 Vector2::One()
{
    return Vector2({1, 1});
}

Vector2 Vector2::Up()
{
    return Vector2({0, -1});
}

Vector2 Vector2::Down()
{
    return Vector2({0, 1});
}

Vector2 Vector2::Left()
{
    return Vector2({-1, 0});
}

Vector2 Vector2::Right()
{
    return Vector2({1, 0});
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
    t = clamp(t, 0.f, 1.f);
    return a + (b - a) * t;
}

bool Vector2::operator==(const Vector2& kVector2)
{
    return x_ == kVector2.x_ && y_ == kVector2.y_;
}

bool Vector2::operator!=(const Vector2& kVector2)
{
    return x_ != kVector2.x_ || y_ != kVector2.y_;
}

void Vector2::Set(float x_, float y_)
{
    this->x_ = x_;
    this->y_ = y_;
}

void Vector2::Normalize()
{
    float m = sqrt(pow(x_, 2) + pow(y_, 2));

    if (m > 0)
    {
        x_ /= m;
        y_ /= m;
    }
    else
    {
        x_ = 0;
        y_ = 0;
    }
}

float Vector2::Magnitude()
{
    return sqrt(pow(x_, 2) + pow(y_, 2));
}

float Vector2::Distance(Vector2 first, Vector2 second)
{
    Vector2 sub = first - second;
    return sub.Magnitude();
}
