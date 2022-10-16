#include "pch.h"
#include "Player.h"
#include "Rigidbody2D.h"
#include "BoxCollider2D.h"
#include "Core.h"

#include <tchar.h>

using namespace std;
using namespace Gdiplus;

Player::Player() : timer_()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetOffset({ 0, 0 });
	GetBoxCollider2D()->SetScale({ 64, 64 });
	AddRigidbody2D();

	bitmap_ = (HBITMAP)LoadImage(NULL, L"Resources/AnimationSheet_Character.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	memDC_ = CreateCompatibleDC(Core::GetInstance()->GetHDC());

	HBITMAP old_bitmap = (HBITMAP)SelectObject(memDC_, bitmap_);
	DeleteObject(old_bitmap);
}

Player::~Player()
{
	DeleteDC(memDC_);
}

void Player::Update(float delta_time)
{
	HWND hWnd = GetFocus();

	float move_speed = 300;

	float horizontal = 0;
	float vertical = 0;
	Vector2 position;

	shared_ptr<Rigidbody2D> rigid = GetRigidbody2D();

	if (hWnd != nullptr)
	{
		if (GetKey(VK_LEFT))
		{
			//Translate(Vector2().Left() * move_speed * delta_time);
			//horizontal = -1;
			rigid->AddForce(Vector2().Left() * move_speed);
		}

		if (GetKey(VK_RIGHT))
		{
			//Translate(Vector2().Right() * move_speed * delta_time);
			//horizontal = 1;
			rigid->AddForce(Vector2().Right() * move_speed);
		}

		if (GetKey(VK_UP))
		{
			//Translate(Vector2().Up() * move_speed * delta_time);
			//vertical = -1;
			rigid->AddForce(Vector2().Up() * move_speed);
		}

		if (GetKey(VK_DOWN))
		{
			//Translate(Vector2().Down() * move_speed * delta_time);
			//vertical = 1;
			rigid->AddForce(Vector2().Down() * move_speed);
		}
	}

	//position.Set(horizontal, vertical);
	//position = position.Normalized() * move_speed * delta_time;
	//SetPosition(GetPosition() + position);

	timer_ += delta_time;

	if (timer_ >= 1)
	{
		_cprintf("Velocity: X: %.f, Y: %.f\n", rigid->GetVelocity().x, rigid->GetVelocity().y);
		timer_ = 0;
	}
}

void Player::LateUpdate(float delta_time)
{
	Object::LateUpdate(delta_time);
}

void Player::Render(HDC hdc)
{
	//Graphics graphics(hdc);

	//graphics.DrawImage(img_, GetRenderPosition().x, GetRenderPosition().y, GetScale().x, GetScale().y);

	TransparentBlt(hdc, GetPivotPosition().x, GetPivotPosition().y, GetScale().x, GetScale().y, memDC_, 32, 0, 32, 32, RGB(0, 255, 38));
}

void Player::OnTriggerEnter(shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	_cprintf("Enter\n");
#endif // _DEBUG
}

void Player::OnTriggerStay(shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	//_cprintf("Stay\n");
#endif // _DEBUG
}

void Player::OnTriggerExit(shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	_cprintf("Exit\n");
#endif // _DEBUG
}
