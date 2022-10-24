#include "pch.h"
#include "Texture.h"
#include "Window.h"

#include <cassert>

Texture::Texture() :
	bitmap_(),
	bitmap_info_(),
	memDC()
{
}

Texture::~Texture()
{
	DeleteDC(memDC);
	DeleteObject(bitmap_);
}

Texture& Texture::operator=(const Texture& kTexture)
{
	bitmap_ = kTexture.bitmap_;
	bitmap_info_ = kTexture.bitmap_info_;
	memDC = kTexture.memDC;
	return *this;
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

LONG Texture::GetWidth()
{
	return bitmap_info_.bmWidth;
}

LONG Texture::GetHeight()
{
	return bitmap_info_.bmHeight;
}
