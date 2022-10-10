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
