#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<CollisionManager> CollisionManager::instance_ = nullptr;
once_flag CollisionManager::flag_;

CollisionManager::CollisionManager() :
	collision_matrix_{}
{
}

std::shared_ptr<CollisionManager> CollisionManager::GetInstance()
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

				const list<shared_ptr<Object>>& first_layer = current_scene->GetLayerObjects((LayerType)row);
				const list<shared_ptr<Object>>& second_layer = current_scene->GetLayerObjects((LayerType)column);
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
