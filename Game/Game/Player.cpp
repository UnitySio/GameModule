#include "Player.h"
#include "framework.h"

void Player::Update(float delta_time)
{
	Vector2 position = GetPosition();

    float move_speed = 300 * delta_time;

    if (GetKeyDown(VK_LEFT))
    {
        position.x_ -= move_speed;
    }

    if (GetKeyDown(VK_RIGHT))
    {
        position.x_ += move_speed;
    }

    if (GetKeyDown(VK_UP))
    {
        position.y_ -= move_speed;
    }

    if (GetKeyDown(VK_DOWN))
    {
        position.y_ += move_speed;
    }

	SetPosition(position);
}

void Player::LateUpdate(float delta_time)
{

}

void Player::Render(HDC hdc)
{
	Graphics graphics(hdc);
	Pen black_pen(Color(255, 0, 0, 0));
	graphics.DrawRectangle(&black_pen, GetPosition().x_, GetPosition().y_, GetScale().x_, GetScale().y_);
}
