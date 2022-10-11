#include "pch.h"
#include "Player.h"

#include <tchar.h>

using namespace Gdiplus;

Player::Player()
{
}

void Player::Update(float delta_time)
{
    HWND hWnd = GetFocus();

    float move_speed = 300;

    float horizontal = 0;
    float vertical = 0;
    Vector2 position;

    if (hWnd != nullptr)
    {
        if (GetKeyDown(VK_LEFT))
        {
            //Translate(Vector2().Left() * move_speed * delta_time);
            horizontal = -1;
        }

        if (GetKeyDown(VK_RIGHT))
        {
            //Translate(Vector2().Right() * move_speed * delta_time);
            horizontal = 1;
        }

        if (GetKeyDown(VK_UP))
        {
            //Translate(Vector2().Up() * move_speed * delta_time);
            vertical = -1;
        }

        if (GetKeyDown(VK_DOWN))
        {
            //Translate(Vector2().Down() * move_speed * delta_time);
            vertical = 1;
        }
    }

    position.Set(horizontal, vertical);
    position = position.Normalized() * move_speed * delta_time;
    SetPosition(GetPosition() + position);
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

    graphics.DrawRectangle(&black_pen, GetRenderPositon().x, GetRenderPositon().y, GetScale().x, GetScale().y);

    PointF pivot_font_position(GetPosition().x, GetPosition().y);
    graphics.DrawString(L"Pivot", -1, &font_style, pivot_font_position, &black_brush);
    graphics.DrawEllipse(&red_pen, GetPosition().x - 2.5, GetPosition().y - 2.5, 5, 5);

    StringFormat string_format;
    string_format.SetAlignment(StringAlignmentCenter);

    WCHAR position_word[1024];
    _stprintf_s(position_word, L"X: %.f, Y: %.f", GetPosition().x, GetPosition().y);
    PointF scene_font_position(GetRenderPositon().x + 16, GetRenderPositon().y + 32);
    graphics.DrawString(position_word, -1, &font_style, scene_font_position, &string_format, &black_brush);

}
