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

CollisionManager::CollisionManager() : collision_matrix_{}, collision_info_{}
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

void CollisionManager::LateUpdate(float delta_time)
{
	for (size_t row = 0; row < (size_t)LayerType::kEnd; row++)
	{
		for (size_t column = 0; column < (size_t)LayerType::kEnd - row; column++)
		{
			if (collision_matrix_[row][column])
			{
				shared_ptr<Scene> current_scene = SceneManager::GetInstance()->GetCurrentScene();

				const vector<shared_ptr<Object>>& first_layer = current_scene->GetGroupObject((LayerType)row);
				const vector<shared_ptr<Object>>& second_layer = current_scene->GetGroupObject((LayerType)column);

				map<ULONGLONG, bool>::iterator iter;

				for (size_t i = 0; i < first_layer.size(); i++)
				{
					if (first_layer[i]->GetBoxCollider2D() == nullptr)
					{
						continue;
					}

					size_t idx = first_layer == second_layer ? i + 1 : 0;

					for (size_t j = idx; j < second_layer.size(); j++)
					{
						if (second_layer[j]->GetBoxCollider2D() == nullptr)
						{
							continue;
						}

						shared_ptr<BoxCollider2D> first = first_layer[i]->GetBoxCollider2D();
						shared_ptr<BoxCollider2D> second = second_layer[j]->GetBoxCollider2D();

						COLLIDER_UID UID;
						UID.first_collider_uid = first->GetUID();
						UID.second_collider_uid = second->GetUID();

						iter = collision_info_.find(UID.UID);

						if (iter == collision_info_.end())
						{
							collision_info_.insert({ UID.UID, false });
							iter = collision_info_.find(UID.UID);
						}

						if (IsCollision(first, second))
						{
							if (iter->second)
							{
								first->OnTriggerStay(second);
								second->OnTriggerStay(first);
							}
							else
							{
								first->OnTriggerEnter(second);
								second->OnTriggerEnter(first);
								iter->second = true;
							}
						}
						else
						{
							if (iter->second)
							{
								first->OnTriggerExit(second);
								second->OnTriggerExit(first);
								iter->second = false;
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::SetCollisionMatrix(LayerType first_layer, LayerType second_layer)
{
	size_t row = (size_t)first_layer; // 세로
	size_t column = (size_t)second_layer; // 가로

	if (column < row)
	{
		row = (size_t)second_layer;
		column = (size_t)first_layer;
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

bool CollisionManager::IsCollision(shared_ptr<BoxCollider2D> first_layer, shared_ptr<BoxCollider2D> second_layer)
{
	Vector2 first_layer_position = first_layer->GetPosition();
	Vector2 first_layer_scale = first_layer->GetScale();

	Vector2 second_layer_position = second_layer->GetPosition();
	Vector2 second_layer_scale = second_layer->GetScale();

	if (fabs(first_layer_position.x - second_layer_position.x) < (first_layer_scale.x + second_layer_scale.x) / 2 && fabs(first_layer_position.y - second_layer_position.y) < (first_layer_scale.y + second_layer_scale.y) / 2)
	{
		return true;
	}

	return false;
}