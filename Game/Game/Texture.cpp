#include "pch.h"
#include "Texture.h"
#include "Window.h"

using namespace std;

Texture::Texture() :
    bitmap_(),
    bitmap_info_(),
    memDC(),
    pivot_{},
    frame_size_{},
    frames_{}
{
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteObject(bitmap_);
}

void Texture::Load(LPCWSTR path, UINT column, UINT row)
{
    bitmap_ = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    memDC = CreateCompatibleDC(WINDOW->GetHDC());

    HBITMAP old_bitmap = (HBITMAP)SelectObject(memDC, bitmap_);
    DeleteObject(old_bitmap);

    GetObject(bitmap_, sizeof(BITMAP), &bitmap_info_);

    frame_size_.x_ = bitmap_info_.bmWidth / column;
    frame_size_.y_ = bitmap_info_.bmHeight / row;

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            Vector2 frame = {frame_size_.x_ * j, frame_size_.y_ * i};
            frames_.push_back({frame});
        }
    }
}

void Texture::SetPivot(Vector2 pivot)
{
    pivot_ = pivot;
}

BITMAP Texture::GetBitmapInfo()
{
    return bitmap_info_;
}

HDC Texture::GetMemDC()
{
    return memDC;
}

Vector2 Texture::GetPivot()
{
    return pivot_;
}

Vector2 Texture::GetSpriteSize()
{
    return frame_size_;
}

const vector<Vector2>& Texture::GetFrames()
{
    return frames_;
}
