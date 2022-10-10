#include "pch.h"
#include "Player.h"

#include <tchar.h>

using namespace Gdiplus;

Player::Player()
{
}

void Player::Update(float delta_time)
{
    Vector2 position = GetPosition();

    float move_speed = 300 * delta_time;

    HWND hWnd = GetFocus();

    if (hWnd != nullptr)
    {
        if (GetKeyDown(VK_LEFT))
        {
            position.x -= move_speed;
        }

        if (GetKeyDown(VK_RIGHT))
        {
            position.x += move_speed;
        }

        if (GetKeyDown(VK_UP))
        {
            position.y -= move_speed;
        }

        if (GetKeyDown(VK_DOWN))
        {
            position.y += move_speed;
        }
    }

	SetPosition(position);
}

void Player::LateUpdate(float delta_time)
{
}

void Player::Render(HDC hdc)
{
    Graphics graphics(hdc);

    FontFamily arial_font(L"Arial");
    Font font_style(&arial_font, 12, FontStyleBold, UnitPixel);

    SolidBrush black_brush(Color(255, 0, 0, 0));

    Pen black_pen(Color(255, 0, 0, 0));
    Pen red_pen(Color(255, 255, 0, 0));

    Vector2 final_position = GetPosition() - GetScale() * 0.5f;

    graphics.DrawRectangle(&black_pen, final_position.x, final_position.y, GetScale().x, GetScale().y);

    PointF pivot_font_position(GetPosition().x, GetPosition().y);
    graphics.DrawString(L"Pivot", -1, &font_style, pivot_font_position, &black_brush);
    graphics.DrawEllipse(&red_pen, GetPosition().x - 2.5, GetPosition().y - 2.5, 5, 5);

    StringFormat string_format;
    string_format.SetAlignment(StringAlignmentCenter);

    WCHAR position_word[1024];
    _stprintf_s(position_word, L"X: %.f, Y: %.f", GetPosition().x, GetPosition().y);
    PointF scene_font_position(final_position.x + 16, final_position.y + 32);
    graphics.DrawString(position_word, -1, &font_style, scene_font_position, &string_format, &black_brush);

}
