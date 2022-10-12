#include "pch.h"
#include "Block.h"
#include "BoxCollider2D.h"

#include <tchar.h>

using namespace std;
using namespace Gdiplus;

Block::Block()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetOffset({ 0.f, 0.f });
	GetBoxCollider2D()->SetScale({ 32.f, 32.f });
}

void Block::Update(float delta_time)
{
}

void Block::LateUpdate(float delta_time)
{
	Object::LateUpdate(delta_time);
}

void Block::Render(HDC hdc)
{
	Graphics graphics(hdc);

	FontFamily arial_font(L"Arial");
	Font font_style(&arial_font, 12, FontStyleBold, UnitPixel);

	SolidBrush black_brush(Color(255, 0, 0, 0));

	Pen black_pen(Color(255, 0, 0, 0));
	Pen red_pen(Color(255, 255, 0, 0));

	graphics.DrawRectangle(&black_pen, GetRenderPositon().x, GetRenderPositon().y, GetScale().x, GetScale().y);

	PointF pivot_font_position(GetPosition().x, GetPosition().y);
	graphics.DrawString(L"Pivot", -1, &font_style, pivot_font_position, &black_brush);
	graphics.DrawEllipse(&red_pen, GetPosition().x - 2.5, GetPosition().y - 2.5, 5, 5);

	StringFormat string_format;
	string_format.SetAlignment(StringAlignmentCenter);

	graphics.DrawLine(&red_pen, 320, 240, (int)GetPosition().x, (int)GetPosition().y);
	float distance = Vector2().Distance({ 320, 240 }, GetPosition());

	WCHAR position_word[1024];
	_stprintf_s(position_word, L"Distance: %.f", distance);
	PointF scene_font_position(GetRenderPositon().x + 16, GetRenderPositon().y + 32);
	graphics.DrawString(position_word, -1, &font_style, scene_font_position, &string_format, &black_brush);
}
