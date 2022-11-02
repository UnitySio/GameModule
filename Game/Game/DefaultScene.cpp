#include "pch.h"
#include "DefaultScene.h"
#include "Object.h"
#include "Player.h"
#include "GroundObject.h"
#include "CollisionManager.h"

using namespace std;

DefaultScene::DefaultScene()
{
}

void DefaultScene::Enter()
{
	shared_ptr<Object> player = make_shared<Player>();
	CreateObject(player, LayerType::kDefault, L"Player", { 320.f, 240.f }, { 0.f, 0.f }, { 3.f, 3.f });

	shared_ptr<Object> ground = make_shared<GroundObject>();
	CreateObject(ground, LayerType::kDefault, L"Ground", { 0.f, 240 }, { 0.f, 0.f }, { 1.f, 1.f });

	shared_ptr<Object> ground_ = make_shared<GroundObject>();
	CreateObject(ground_, LayerType::kDefault, L"Ground", { 640.f, 240 }, { 0.f, 0.f }, { 1.f, 1.f });

	COLLISION_MANAGER->SetCollisionMatrix(LayerType::kDefault, LayerType::kDefault);
}

void DefaultScene::Exit()
{
}
