#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "BoxCollider2D.h"
#include "InputManager.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerJump.h"
#include "PlayerFalling.h"

using namespace std;

shared_ptr<State> Player::GetInitiateState()
{
    return states_[(size_t)PlayerStateType::kIdle];
}

Player::Player() :
    move_speed_(200.f),
    jump_force_(500.f),
    direction_(1),
    is_ground_(),
    is_attack_(),
    horizontal_()
{
    // 상태 추가
    states_[(size_t)PlayerStateType::kIdle] = make_shared<PlayerIdle>(this);
    states_[(size_t)PlayerStateType::kWalk] = make_shared<PlayerWalk>(this);
    states_[(size_t)PlayerStateType::kJump] = make_shared<PlayerJump>(this);
    states_[(size_t)PlayerStateType::kFalling] = make_shared<PlayerFalling>(this);

    // 추후 리소스 매니저에서 리소스들을 관리할 수 있도록 변경 예정
    right_ = make_shared<Texture>();
    right_->Load(L"Resources/WarriorRightSheet.bmp", 6, 17);
    right_->SetPivot({0.385f, 0.97f});

    left_ = make_shared<Texture>();
    left_->Load(L"Resources/WarriorLeftSheet.bmp", 6, 17);
    left_->SetPivot({0.625f, 0.97f});

    AddSpriteRenderer(); // 스프라이트 랜더러 컴포넌트
    GetSpriteRenderer()->SetTexture(right_);

    AddAnimator(); // 애니메이터 컴포넌트
    GetAnimator()->AddClip(L"IDLE", true, 0, 6); // IDLE 애니메이션
    GetAnimator()->AddClip(L"WALK", true, 6, 8); // WALK 애니메이션
    GetAnimator()->AddClip(L"JUMP", false, 41, 3); // JUMP 애니메이션
    GetAnimator()->AddClip(L"FALLING", false, 44, 5); // FALLING 애니메이션

    AddRigidbody2D(); // 리자드 바디 컴포넌트
    AddBoxCollider2D(); // 박스 콜라이더 컴폰넌트
    GetBoxCollider2D()->SetOffset({0.f, -50.f});
    GetBoxCollider2D()->SetSize({64.f, 100.f});

    // 상태 머신 초기화
    StateMachine::Initiate();
}

void Player::Update()
{
    Object::Update();
    StateMachine::Update();

    // 땅이 아닐 경우 아래방향으로 중력 가속도를 줌
    if (!is_ground_)
    {
        GetRigidbody2D()->SetGravityAcceleration(Vector2().Down() * 800.f);
    }
}

void Player::LateUpdate()
{
    Object::LateUpdate();
}

void Player::PhysicsUpdate()
{
    Object::PhysicsUpdate();
}

void Player::Render()
{
    Object::Render();
}

void Player::OnTriggerEnter(Object* other)
{
    if (wcscmp(other->GetName(), L"Ground") == 0)
    {
        is_ground_ = true;
        GetRigidbody2D()->SetVelocity({GetRigidbody2D()->GetVelocity().x_, 0.f});
    }
}

void Player::OnTriggerStay(Object* other)
{
}

void Player::OnTriggerExit(Object* other)
{
    if (wcscmp(other->GetName(), L"Ground") == 0)
    {
        is_ground_ = false;
    }
}

void Player::Movement()
{
    shared_ptr<Rigidbody2D> rigid = GetRigidbody2D();
    shared_ptr<SpriteRenderer> sprite = GetSpriteRenderer();

    // D입력 시 1, A 입력 시 -1, 입력되지 않을 경우 0
    horizontal_ = (INPUT->GetKey(RIGHT) - INPUT->GetKey(LEFT));

    rigid->SetVelocity({move_speed_ * horizontal_, rigid->GetVelocity().y_});

    if (INPUT->GetKeyDown(JUMP))
    {
        if (is_ground_)
        {
            rigid->SetVelocity({rigid->GetVelocity().x_, -jump_force_});
        }
    }

    if (INPUT->GetKeyDown(RUN))
    {
        move_speed_ = 400.f;
    }

    if (INPUT->GetKeyUp(RUN))
    {
        move_speed_ = 200.f;
    }

    if (rigid->GetVelocity().x_ > 0.f)
    {
        direction_ = 1;
        sprite->SetTexture(right_);
    }
    else if (rigid->GetVelocity().x_ < 0.f)
    {
        direction_ = -1;
        sprite->SetTexture(left_);
    }

    if (is_ground_)
    {
        if (rigid->GetVelocity().x_ != 0.f)
        {
            if (current_state_ != states_[(size_t)PlayerStateType::kWalk])
            {
                ChangeState(states_[(size_t)PlayerStateType::kWalk]);
            }
        }
        else if (rigid->GetVelocity().x_ == 0.f)
        {
            if (current_state_ != states_[(size_t)PlayerStateType::kIdle])
            {
                ChangeState(states_[(size_t)PlayerStateType::kIdle]);
            }
        }
    }
    else
    {
        if (rigid->GetVelocity().y_ < 0.f)
        {
            if (current_state_ != states_[(size_t)PlayerStateType::kJump])
            {
                ChangeState(states_[(size_t)PlayerStateType::kJump]);
            }
        }
        else if (rigid->GetVelocity().y_ > 0.f)
        {
            if (current_state_ != states_[(size_t)PlayerStateType::kFalling])
            {
                ChangeState(states_[(size_t)PlayerStateType::kFalling]);
            }
        }
    }
}
