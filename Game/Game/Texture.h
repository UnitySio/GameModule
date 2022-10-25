#pragma once
class Texture
{
private:
	friend class SpriteRenderer;

	HBITMAP bitmap_;

	BITMAP bitmap_info_;

	HDC memDC;

	Vector2 pivot_;
public:
	Texture();
	~Texture();

	void Load(LPCWSTR path);
	void SetPivot(Vector2 pivot);

	int GetWidth();
	int GetHeight();
};

