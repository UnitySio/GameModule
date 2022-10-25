#include "pch.h"
#include "Texture.h"
#include "Window.h"

#include <cassert>

Texture::Texture() :
	bitmap_(),
	bitmap_info_(),
	memDC(),
	pivot_{}
{
}

Texture::~Texture()
{
	DeleteDC(memDC);
	DeleteObject(bitmap_);
}

void Texture::Load(LPCWSTR path)
{
	bitmap_ = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert(bitmap_);

	memDC = CreateCompatibleDC(Window::GetInstance()->GetHDC());

	HBITMAP old_bitmap = (HBITMAP)SelectObject(memDC, bitmap_);
	DeleteObject(old_bitmap);

	GetObject(bitmap_, sizeof(BITMAP), &bitmap_info_);
}

void Texture::SetPivot(Vector2 pivot)
{
	pivot_ = pivot;
}

int Texture::GetWidth()
{
	return bitmap_info_.bmWidth;
}

int Texture::GetHeight()
{
	return bitmap_info_.bmHeight;
}
