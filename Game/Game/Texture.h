#pragma once
class Texture
{
private:
	friend class SpriteRenderer;

	HBITMAP bitmap_;

	BITMAP bitmap_info_;

	HDC memDC;
public:
	Texture();
	~Texture();

	Texture& operator=(const Texture& kTexture);

	void Load(LPCWSTR path);

	LONG GetWidth();
	LONG GetHeight();
};

