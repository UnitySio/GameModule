#pragma once
class Texture
{
private:
    HBITMAP bitmap_;

    BITMAP bitmap_info_;

    HDC memDC;

    Vector2 pivot_;
    Vector2 frame_size_;

    std::vector<Vector2> frames_;
public:
    Texture();
    ~Texture();

    void Load(LPCWSTR path, UINT column = 1, UINT row = 1);
    void SetPivot(Vector2 pivot);

    BITMAP GetBitmapInfo();

    HDC GetMemDC();

    Vector2 GetPivot();
    Vector2 GetSpriteSize();

    const std::vector<Vector2>& GetFrames();
};
