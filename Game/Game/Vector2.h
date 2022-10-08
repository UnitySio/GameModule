#pragma once
class Vector2
{
private:
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	~Vector2() = default;

	float x_;
	float y_;
};

