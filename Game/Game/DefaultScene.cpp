#include "pch.h"
#include "DefaultScene.h"
#include "Boss.h"
#include "Object.h"
#include "Player.h"
#include "Ground.h"
#include "Combo.h"
#include "CollisionManager.h"
#include "Camera.h"

using namespace std;

void DefaultScene::Enter()
{
	shared_ptr<Object> ground = make_shared<Ground>();
	CreateObject(ground, LayerType::kGround, L"Ground", { 800.f, 768.f }, { 1.f, 1.f });

	shared_ptr<Object> player = make_shared<Player>();
	CreateObject(player, LayerType::kPlayer, L"Player", { 600.f, 600.f }, { 3.f, 3.f });

	shared_ptr<Object> boss = make_shared<Boss>();
	CreateObject(boss, LayerType::kBoss, L"Boss", { 200.f, 600.f }, { 3.f, 3.f });
	(*(Boss*)boss.get()).SetTarget(player);

	shared_ptr<Object> combo = make_shared<Combo>();
	CreateObject(combo, LayerType::kUI, L"Combo", {}, {});

	COLLISION->SetCollisionMatrix(LayerType::kGround, LayerType::kPlayer);
	COLLISION->SetCollisionMatrix(LayerType::kPlayer, LayerType::kBossHitBox);
	COLLISION->SetCollisionMatrix(LayerType::kGround, LayerType::kBoss);
	COLLISION->SetCollisionMatrix(LayerType::kPlayerHitBox, LayerType::kBoss);

	CAMERA->SetTarget(player);
	CAMERA->SetLimitArea({ 0.f, 0.f, 1600.f, 800.f });
}

void DefaultScene::Exit()
{
	Scene::Exit();
}
