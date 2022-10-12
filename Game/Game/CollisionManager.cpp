#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "BoxCollider2D.h"

using namespace std;

// 멤버 변수 초기화
unique_ptr<CollisionManager> CollisionManager::instance_ = nullptr;
once_flag CollisionManager::flag_;

CollisionManager::CollisionManager() : collision_matrix_{}, info{}
{
}

CollisionManager* CollisionManager::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new CollisionManager);
        });

    return instance_.get();
}

void CollisionManager::Initiate()
{

}

void CollisionManager::Update(float delta_time)
{
    for (size_t row = 0; row < (size_t)GroupObjectType::kEND; row++)
    {
        for (size_t column = row; column < (size_t)GroupObjectType::kEND; column++)
        {
            if (collision_matrix_[row][column])
            {
                shared_ptr<Scene> current_scene = SceneManager::GetInstance()->GetCurrentScene();

                const vector<shared_ptr<Object>>& group1 = current_scene->GetGroupObject((GroupObjectType)row);
                const vector<shared_ptr<Object>>& group2 = current_scene->GetGroupObject((GroupObjectType)column);

                map<ULONGLONG, bool>::iterator iter;

                for (size_t i = 0; i < group1.size(); i++)
                {
                    if (group1[i]->GetBoxCollider2D() == nullptr)
                    {
                        continue;
                    }

                    for (size_t j = 0; j < group2.size(); j++)
                    {
                        if (group2[i]->GetBoxCollider2D() == nullptr || group1[i] == group2[j])
                        {
                            continue;
                        }

                        COLLIDER_UID UID;
                        UID.group1_uid = group1[i]->GetBoxCollider2D()->GetUID();
                        UID.group2_uid = group2[j]->GetBoxCollider2D()->GetUID();

                        iter = info.find(UID.UID);

                        if (info.end() == iter)
                        {
                            info.insert({ UID.UID, false });
                            iter = info.find(UID.UID);
                        }

                        if (IsCollision(group1[i]->GetBoxCollider2D(), group2[j]->GetBoxCollider2D()))
                        {
                            if (iter->second)
                            {
                                group1[i]->GetBoxCollider2D()->OnTriggerStay(group2[j]->GetBoxCollider2D());
                                group2[j]->GetBoxCollider2D()->OnTriggerStay(group1[i]->GetBoxCollider2D());
                            }
                            else
                            {
                                group1[i]->GetBoxCollider2D()->OnTriggerEnter(group2[j]->GetBoxCollider2D());
                                group2[j]->GetBoxCollider2D()->OnTriggerEnter(group1[i]->GetBoxCollider2D());
                                iter->second = true;
                            }
                        }
                        else
                        {
                            if (iter->second)
                            {
                                group1[i]->GetBoxCollider2D()->OnTriggerExit(group2[j]->GetBoxCollider2D());
                                group2[j]->GetBoxCollider2D()->OnTriggerExit(group1[i]->GetBoxCollider2D());
                                iter->second = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void CollisionManager::SetCollisionMatrix(GroupObjectType group1, GroupObjectType group2)
{
    size_t row = (size_t)group1; // 세로
    size_t column = (size_t)group2; // 가로

    if (column < row)
    {
        row = (size_t)group2;
        column = (size_t)group1;
    }

    if (collision_matrix_[row][column])
    {
        collision_matrix_[row][column] = false;
    }
    else
    {
        collision_matrix_[row][column] = true;
    }
}

bool CollisionManager::IsCollision(shared_ptr<BoxCollider2D> group1, shared_ptr<BoxCollider2D> group2)
{
    Vector2 group1_position = group1->GetPosition();
    Vector2 group1_scale = group1->GetScale();

    Vector2 group2_position = group2->GetPosition();
    Vector2 group2_scale = group2->GetScale();

    if (abs(group2_position.x - group1_position.x) < (group2_scale.x + group1_scale.x) / 2.f && abs(group2_position.y - group1_position.y) < (group2_scale.y + group1_scale.y) / 2.f)
    {
        return true;
    }

    return false;
}