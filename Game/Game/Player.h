#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Entity.h"
#include "Texture.h"

class Player :
    public Object, // ������Ʈ
    public StateMachine, // ���� ���� �ӽ�
    public Entity // ��ƼƼ
{
private:
    // �� ���� Ŭ�������� ������ �� �ֵ��� friend�� ����
    friend class PlayerIdle;
    friend class PlayerWalk;
    friend class PlayerDash;
    friend class PlayerJump;
    friend class PlayerFalling;
    friend class PlayerAttack;
    friend class PlayerHit;
    friend class PlayerDeath;

    float move_speed_;
    float jump_force_;

    std::shared_ptr<State> states_[(size_t)PlayerStateType::kEnd];

    std::shared_ptr<Texture> left_;
    std::shared_ptr<Texture> right_;

    bool is_ground_;
    bool is_dash_;

    int horizontal_;
    int direction_;

    void Movement();
protected:
    std::shared_ptr<State> GetInitiateState() final;
public:
    Player();
    ~Player() final = default;

    void Update() final;
    void LateUpdate() final;
    void PhysicsUpdate() final;
    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
    void OnDamage(UINT damage) final;
    void OnDeath() final;

    bool IsDash();
};
