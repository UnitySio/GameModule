#include "pch.h"
#include "Rigidbody2D.h"

using namespace std;

Rigidbody2D::Rigidbody2D() : owner_(), mass_(1), force_{}, acceleration_{}, velocity_{}
{
}

void Rigidbody2D::LateUpdate(float delta_time)
{
	// F = m * a (�� = ���� * ���ӵ�)
	// A = f / m (���ӵ� = �� / ����)
	acceleration_ = force_ / mass_;
	velocity_ += acceleration_ * delta_time;

	// ������
	/*if (velocity_ != Vector2().Zero())
	{
		// ���� ������ ������ �ݴ� ����
		Vector2 friction_direction = velocity_ * -1;

		friction_ = friction_direction.Normalized() * 40 * delta_time;

		velocity_ += friction_;
	}*/

	// ������Ʈ���� ����
	Vector2 position = owner_->GetPosition();
	position += velocity_ * delta_time;

	owner_->SetPosition(position);

	// ������ �� �ʱ�ȭ
	force_ = Vector2().Zero();
}

void Rigidbody2D::AddForce(Vector2 force)
{
	force_ += force; // �� ����
}
