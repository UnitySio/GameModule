#pragma once
class Sprite
{
private:
	HBITMAP bitmap_;

	HDC memDC;
public:
	Sprite();
	~Sprite();

	void Load(LPCWSTR path);
};
