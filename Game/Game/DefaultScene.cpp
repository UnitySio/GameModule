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
	CreateObject(player, LayerType::kDefault, L"Player", { 32.f, 32.f }, { 0.f, 0.f }, { 64.f, 64.f });
}

void DefaultScene::Exit()
{
}
