#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DefaultScene.h"
#include "Object.h"

using namespace std;
using namespace Gdiplus;

// 멤버 변수 초기화
shared_ptr<SceneManager> SceneManager::instance_ = nullptr;
once_flag SceneManager::flag_;

SceneManager::SceneManager() :
	scenes_(),
	current_scene_()
{
}

shared_ptr<SceneManager> SceneManager::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new SceneManager);
		});

	return instance_;
}

void SceneManager::Release()
{
	instance_.reset();
}

void SceneManager::Initiate()
{
	shared_ptr<Scene> default_scene = make_shared<DefaultScene>();
	CreateScene(default_scene, SceneType::kDefault, L"Default");

	LoadScene(SceneType::kDefault);
}

void SceneManager::CreateScene(std::shared_ptr<Scene> scene, SceneType scene_type, LPCWSTR name)
{
	scene->SetName(name);

	scenes_[(size_t)scene_type] = scene;
}

void SceneManager::LoadScene(SceneType scene_type)
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Exit();
	}

	current_scene_ = scenes_[(size_t)scene_type];
	current_scene_->Enter();
}

void SceneManager::InputUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->InputUpdate();
	}
}

void SceneManager::Update()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Update();
	}
}

void SceneManager::LateUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->LateUpdate();
	}
}

void SceneManager::PhysicsUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->PhysicsUpdate();
	}
}

void SceneManager::Render()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Render();
	}
}

void SceneManager::ObjectUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->ObjectUpdate();
	}
}

void SceneManager::Destroy(Object* object)
{
	object->SetDestroy();
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return current_scene_;
}
