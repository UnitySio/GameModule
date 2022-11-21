#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"

class Boss :
    public Object,
    public StateMachine
{
private:
    std::shared_ptr<Object> target_;
    
    std::shared_ptr<Texture> left_idle_;
    std::shared_ptr<Texture> left_run_;
    std::shared_ptr<Texture> right_idle_;
    std::shared_ptr<Texture> right_run_;

    bool is_ground_;
    
    int direction_;

    float hp_;
    float max_hp_;
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
};
