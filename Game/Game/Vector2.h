#pragma once
class Vector2
{
private:
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2() = default;

	Vector2 &operator=(const Vector2 &kVector2);
	Vector2 operator+(const Vector2 &kVector2);
	Vector2 operator-(const Vector2 &kVector2);
	Vector2 operator*(float value);
	Vector2 operator/(float value);

	bool operator==(const Vector2 &kVector2);
	bool operator!=(const Vector2 &kVector2);

	float x;
	float y;
};
