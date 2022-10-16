#include "pch.h"
#include "TestScene.h"
#include "Player.h"
#include "Block.h"
#include "CollisionManager.h"

using namespace std;

void TestScene::Enter()
{
	shared_ptr<Object> ground = make_unique<Block>();
	ground->SetName(L"Block 1");
	ground->SetPosition({ 320, 480 });
	ground->SetScale({ 200, 200 });
	ground->SetPivot({ 0.5, 1 });
	CreateObject(ground, LayerType::kDefault);

	shared_ptr<Object> ground2 = make_unique<Block>(*(Block*)ground.get());
	ground2->SetPosition({ 540, 380 });
	CreateObject(ground2, LayerType::kDefault);

	shared_ptr<Object> player = make_shared<Player>();
	player->SetName(L"Player");
	player->SetPosition({ 0, 0 });
	player->SetScale({ 64, 64 });
	player->SetPivot({ 0.5, 0.5 });
	CreateObject(player, LayerType::kDefault);

	//shared_ptr<Object> playera = make_shared<Player>(*(Player*)player.get());
	//playera->SetPosition({ 280, 240 });
	//CreateObject(playera, LayerType::kDEFAULT);

	//CreateObject(o, LayerType::kDEFAULT);

	CollisionManager::GetInstance()->SetCollisionMatrix(LayerType::kDefault, LayerType::kDefault);
}

void TestScene::Exit()
{
}
