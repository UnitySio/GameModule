#include "SceneManager.h"
#include "TestScene.h"

// 멤버 변수 초기화
unique_ptr<SceneManager> SceneManager::instance_ = nullptr;
once_flag SceneManager::flag_;

SceneManager* SceneManager::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new SceneManager);
        });

    return instance_.get();
}

void SceneManager::Initiate()
{
    scenes_[(size_t)SceneType::kTEST] = make_shared<TestScene>();
    scenes_[(size_t)SceneType::kTEST]->SetName(L"Test Scene");
    current_scene_ = scenes_[(size_t)SceneType::kTEST];

    current_scene_->Enter();
}

void SceneManager::Update(float delta_time)
{
    current_scene_->Update(delta_time);
}

void SceneManager::LateUpdate(float delta_time)
{
    current_scene_->LateUpdate(delta_time);
}

void SceneManager::Render(HDC hdc)
{
    current_scene_->Render(hdc);
}
