#include "pch.h"
#include "Texture.h"
#include "Window.h"

#include <cassert>

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

void Texture::Load(LPCWSTR path, UINT row, UINT column)
{
	bitmap_ = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert(bitmap_);

	memDC = CreateCompatibleDC(WINDOW->GetHDC());

	HBITMAP old_bitmap = (HBITMAP)SelectObject(memDC, bitmap_);
	DeleteObject(old_bitmap);

	GetObject(bitmap_, sizeof(BITMAP), &bitmap_info_);

	frame_size_.x_ = bitmap_info_.bmWidth / row;
	frame_size_.y_ = bitmap_info_.bmHeight / column;

	for (size_t i = 0; i < column; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			Vector2 frame = { frame_size_.x_ * j, frame_size_.y_ * i };
			frames_.push_back({ frame });
		}
	}
}

void Texture::SetPivot(Vector2 pivot)
{
	pivot_ = pivot;
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
