#include "pch.h"
#include "Sprite.h"
#include "Window.h"

Sprite::Sprite() :
	bitmap_(),
	memDC()
{
}

Sprite::~Sprite()
{
	DeleteDC(memDC);
}

void Sprite::Load(LPCWSTR path)
{
	bitmap_ = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	memDC = CreateCompatibleDC(Window::GetInstance()->GetHDC());

	HBITMAP old_bitmap = (HBITMAP)SelectObject(memDC, bitmap_);
	DeleteObject(old_bitmap);
}
