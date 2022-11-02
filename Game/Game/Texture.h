#pragma once
class Texture
{
private:
	friend class SpriteRenderer;
	friend class BoxCollider2D;

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
};
