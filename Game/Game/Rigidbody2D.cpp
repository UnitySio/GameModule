#include "pch.h"
#include "Rigidbody2D.h"
#include "Object.h"
#include "Window.h"

Rigidbody2D::Rigidbody2D() :
    owner_(),
    force_{},
    acceleration_{},
    friction_{},
    velocity_{},
    mass_(1.f),
    friction_coefficient_(200.f),
    drag_()
{
}

Rigidbody2D::Rigidbody2D(const Rigidbody2D& kOrigin) :
    owner_(),
    force_{},
    acceleration_{},
    friction_{},
    velocity_{},
    mass_(kOrigin.mass_),
    friction_coefficient_(kOrigin.friction_coefficient_),
    drag_(kOrigin.drag_)
{
}

void Rigidbody2D::SetVelocity(Vector2 velocity)
{
    velocity_ = velocity;
}

void Rigidbody2D::AddForce(Vector2 force)
{
    force_ += force;
}

void Rigidbody2D::SetMass(float mass)
{
    mass_ = mass;
}

void Rigidbody2D::SetFrictionCoefficient(float friction_coefficient)
{
    friction_coefficient_ = friction_coefficient;
}

void Rigidbody2D::SetDrag(float drag)
{
    drag_ = drag;
}

void Rigidbody2D::SetGravityAcceleration(Vector2 acceleration)
{
    gravity_acceleration_ = acceleration;
}

void Rigidbody2D::PhysicsUpdate()
{
    // F = m * a (�� = ���� * ���ӵ�)
    // A = f / m (���ӵ� = �� / ����)
    acceleration_ = force_ / mass_;
    acceleration_ += gravity_acceleration_; // �߷� ���ӵ�
    velocity_ += acceleration_ * DELTA_TIME;

    // F = �� * N (������ = ���� ��� * ���� �׷�)
    if (velocity_ != Vector2().Zero())
    {
        // ������ ����
        Vector2 friction_direction = velocity_ * -1;

        friction_ = friction_direction.Normalized() * friction_coefficient_ * DELTA_TIME;
        velocity_ += friction_;

        // V = V * (1 - D * dt) (���׷�)
        velocity_ = velocity_ * (1 - drag_ * DELTA_TIME);
    }

    owner_->Translate(velocity_ * DELTA_TIME);

    // ������ �� �ʱ�ȭ
    force_ = Vector2().Zero();
    acceleration_ = Vector2().Zero();
    gravity_acceleration_ = Vector2().Zero();
}

Vector2 Rigidbody2D::GetVelocity()
{
    return velocity_;
}
