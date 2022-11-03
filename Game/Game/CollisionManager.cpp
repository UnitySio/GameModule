#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "BoxCollider2D.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<CollisionManager> CollisionManager::instance_ = nullptr;
once_flag CollisionManager::flag_;

CollisionManager::CollisionManager() :
	collision_matrix_{},
	collision_info_{}
{
}

shared_ptr<CollisionManager> CollisionManager::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new CollisionManager);
		});

	return instance_;
}

void CollisionManager::Release()
{
	instance_.reset();
}

void CollisionManager::PhysicsUpdate()
{
	for (size_t row = 0; row < (size_t)LayerType::kEnd; row++)
	{
		for (size_t column = row; column < (size_t)LayerType::kEnd; column++)
		{
			if (collision_matrix_[row][column])
			{
				shared_ptr<Scene> current_scene = SCENE_MANAGER->GetCurrentScene();

				const vector<shared_ptr<Object>>& kFirstLayer = current_scene->GetLayerObjects((LayerType)row);
				const vector<shared_ptr<Object>>& kSecondLayer = current_scene->GetLayerObjects((LayerType)column);

				map<ULONGLONG, bool>::iterator iter;

				for (size_t i = 0; i < kFirstLayer.size(); i++)
				{
					if (kFirstLayer[i]->GetBoxCollider2D() == nullptr)
					{
						continue;
					}

					size_t idx = kFirstLayer == kSecondLayer ? i + 1 : 0;

					for (size_t j = idx; j < kSecondLayer.size(); j++)
					{
						if (kSecondLayer[j]->GetBoxCollider2D() == nullptr)
						{
							continue;
						}

						shared_ptr<BoxCollider2D> first = kFirstLayer[i]->GetBoxCollider2D();
						shared_ptr<BoxCollider2D> second = kSecondLayer[j]->GetBoxCollider2D();

						ColliderUID uid;
						uid.first_collider_uid = first->GetUID();
						uid.second_collider_uid = second->GetUID();

						iter = collision_info_.find(uid.uid);

						if (iter == collision_info_.end())
						{
							collision_info_.insert({ uid.uid, false });
							iter = collision_info_.find(uid.uid);
						}

						if (IsCollision(first, second))
						{
							if (iter->second)
							{
								first->OnTriggerStay(second->GetOwner());
								second->OnTriggerStay(first->GetOwner());
							}
							else
							{
								first->OnTriggerEnter(second->GetOwner());
								second->OnTriggerEnter(first->GetOwner());
								iter->second = true;
							}
						}
						else
						{
							if (iter->second)
							{
								first->OnTriggerExit(second->GetOwner());
								second->OnTriggerExit(first->GetOwner());
								iter->second = false;
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::SetCollisionMatrix(LayerType first, LayerType second)
{
	size_t row = (size_t)first;
	size_t column = (size_t)second;

	if (column < row)
	{
		size_t row = (size_t)second;
		size_t column = (size_t)first;
	}

	collision_matrix_[row][column] = true;
}

bool CollisionManager::IsCollision(shared_ptr<BoxCollider2D> first, shared_ptr<BoxCollider2D> second)
{
	Vector2 first_position = first->GetPosition();
	Vector2 first_scale = first->GetScale();

	Vector2 second_position = second->GetPosition();
	Vector2 second_scale = second->GetScale();

	if (abs(first_position.x_ - second_position.x_) < (first_scale.x_ + second_scale.x_) / 2 &&
		abs(first_position.y_ - second_position.y_) < (first_scale.y_ + second_scale.y_) / 2)
	{
		return true;
	}

	return false;
}
