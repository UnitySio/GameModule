#include "pch.h"
#include "DefaultScene.h"
#include "Object.h"
#include "Player.h"

using namespace std;

DefaultScene::DefaultScene()
{
}

void DefaultScene::Enter()
{
	shared_ptr<Object> player = make_shared<Player>();
	CreateObject(player, LayerType::kDefault, L"Player", { 320.f, 240.f }, { 0.f, 0.f }, { 3.f, 3.f });
}

void DefaultScene::Exit()
{
}
