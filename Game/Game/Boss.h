#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Entity.h"
#include "Texture.h"

class Boss :
    public Object,
    public StateMachine,
    public Entity
{
private:
    std::shared_ptr<Object> target_;
    
    std::shared_ptr<Texture> left_idle_;
    std::shared_ptr<Texture> left_run_;
    std::shared_ptr<Texture> right_idle_;
    std::shared_ptr<Texture> right_run_;

    bool is_ground_;
    
    int direction_;
protected:
    std::shared_ptr<State> GetInitiateState() final;
public:
    Boss();
    ~Boss() final = default;

    void SetTarget(std::shared_ptr<Object> target);
    void Update() final;
    void LateUpdate() final;
    void PhysicsUpdate() final;
    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
    void OnDeath() final;
};
