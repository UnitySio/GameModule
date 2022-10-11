#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2 &Vector2::operator=(const Vector2& kVector2)
{
	x = kVector2.x;
	y = kVector2.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 &kVector2)
{
	return { x + kVector2.x, y + kVector2.y };
}

Vector2 Vector2::operator-(const Vector2 &kVector2)
{
	return { x - kVector2.x, y - kVector2.y };
}

Vector2 Vector2::operator*(const Vector2& kVector2)
{
	return { x * kVector2.x, y * kVector2.y };
}

Vector2 Vector2::operator*(float value)
{
	return { x * value, y * value };
}

Vector2 Vector2::operator/(float value)
{
	return { x / value, y / value };
}

bool Vector2::operator==(const Vector2 &kVector2)
{
	return x == kVector2.x && y == kVector2.y;
}

bool Vector2::operator!=(const Vector2 &kVector2)
{
	return x != kVector2.x || y != kVector2.y;
}

Vector2 Vector2::Normalized()
{
	if (Magnitude() > 0)
	{
		return { x / Magnitude(), y / Magnitude() };
	}

	return { 0, 0 };
}

Vector2 Vector2::Zero()
{
	return { 0, 0 };
}

Vector2 Vector2::One()
{
	return { 1, 1 };
}

Vector2 Vector2::Up()
{
	return { 0, -1 };
}

Vector2 Vector2::Left()
{
	return { -1, 0 };
}

Vector2 Vector2::Down()
{
	return { 0, 1 };
}

Vector2 Vector2::Right()
{
	return { 1, 0 };
}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::Magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2::Distance(Vector2 first, Vector2 second)
{
	Vector2 result = first - second;
	return result.Magnitude();
}
