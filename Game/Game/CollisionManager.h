#pragma once

#include "Singleton.h"

class BoxCollider2D;

class CollisionManager :
    public Singleton<CollisionManager>
{
private:
    union ColliderUID
    {
        struct
        {
            UINT first_collider_uid;
            UINT second_collider_uid;
        };

        ULONGLONG uid;
    };

    std::map<ULONGLONG, bool> collision_info_;
    bool collision_matrix_[(size_t)LayerType::kEnd][(size_t)LayerType::kEnd];
public:
    CollisionManager();
    ~CollisionManager() final = default;

    void PhysicsUpdate();
    void SetCollisionMatrix(LayerType first, LayerType second);
    void Reset();

    bool IsCollision(std::shared_ptr<BoxCollider2D> first, std::shared_ptr<BoxCollider2D> second);
};
