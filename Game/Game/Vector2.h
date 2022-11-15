#pragma once
class Vector2
{
public:
	float x_;
	float y_;

	Vector2();
	Vector2(float x_, float y_);
	~Vector2() = default;

	Vector2& operator+=(const Vector2& kVector2);
	Vector2& operator-=(const Vector2& kVector2);
	Vector2& operator*=(const Vector2& kVector2);
	Vector2& operator/=(const Vector2& kVector2);
	Vector2& operator=(const Vector2& kVector2);

	Vector2 operator+(const Vector2& kVector2);
	Vector2 operator-(const Vector2& kVector2);
	Vector2 operator*(const Vector2& kVector2);
	Vector2 operator/(const Vector2& kVector2);
	Vector2 operator+(float value);
	Vector2 operator-(float value);
	Vector2 operator*(float value);
	Vector2 operator/(float value);
	Vector2 Normalized();
	Vector2 Zero();
	Vector2 One();
	Vector2 Up();
	Vector2 Down();
	Vector2 Left();
	Vector2 Right();
	Vector2 Lerp(Vector2 a, Vector2 b, float t);

	bool operator==(const Vector2& kVector2);
	bool operator!=(const Vector2& kVector2);

	void Set(float x_, float y_);
	void Normalize();

	float Magnitude();
	float Distance(Vector2 first, Vector2 second);
};
