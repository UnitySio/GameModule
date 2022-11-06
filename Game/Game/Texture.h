#pragma once
class Texture
{
private:
	HBITMAP bitmap_;

	BITMAP bitmap_info_;

	HDC memDC;

	Vector2 pivot_;
	Vector2 frame_scale_;

	std::vector<Vector2> frames_;
public:
	Texture();
	~Texture();

	void Load(LPCWSTR path, UINT row = 1, UINT column = 1);
	void SetPivot(Vector2 pivot);

	HDC GetMemDC();

	Vector2 GetPivot();
	Vector2 GetSpriteScale();

	const std::vector<Vector2>& GetFrames();
};
