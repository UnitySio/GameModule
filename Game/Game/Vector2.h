#pragma once
class Vector2
{
private:
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2() = default;

	float x;
	float y;

	Vector2 &operator=(const Vector2 &kVector2);
	Vector2 operator+(const Vector2 &kVector2);
	Vector2 operator-(const Vector2 &kVector2);	
	Vector2 operator*(const Vector2 &kVector2);
	Vector2 operator*(float value);
	Vector2 operator/(float value);

	Vector2 Normalized();
	Vector2 Zero();
	Vector2 One();
	Vector2 Up();
	Vector2 Left();
	Vector2 Down();
	Vector2 Right();

	void Set(float x, float y);

	float Magnitude();
	float Distance(Vector2 first, Vector2 second);

	bool operator==(const Vector2 &kVector2);
	bool operator!=(const Vector2 &kVector2);
};
