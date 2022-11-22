#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"

class Player :
    public Object,
    public StateMachine
{
private:
    // �� ���� Ŭ�������� ������ �� �ֵ��� friend�� ����
    friend class PlayerIdle;
    friend class PlayerWalk;
    friend class PlayerJump;
    friend class PlayerFalling;

    float move_speed_;
    float jump_force_;

    std::shared_ptr<State> states_[4];

    std::shared_ptr<Texture> left_;
    std::shared_ptr<Texture> right_;

    bool is_ground_;

    int horizontal_;
protected:
    std::shared_ptr<State> GetInitiateState() final;
public:
    bool is_attack_;
    int direction_;

    Player();
    ~Player() final = default;

    void Update() final;
    void LateUpdate() final;
    void PhysicsUpdate() final;
    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
    
    void Movement();
};
