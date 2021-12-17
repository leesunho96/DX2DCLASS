#include "stdafx.h"
#include "Stage2.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Viewer/Freedom.h"
#include "Objects/Background_Yeti.h"
#include "Systems/CollisionSystem.h"

extern CollisionSystem* collisionsystem;

Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	bg = new Background_Yeti();
	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
	collisionsystem = new CollisionSystem(values, player);
	player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));

	//collisionsystem->PushMarkerByCode(D3DXVECTOR2(0, 0));
	//collisionsystem->PushMarkerByCode(D3DXVECTOR2(100, 100));

}

Stage2::~Stage2()
{
	SAFE_DELETE(collisionsystem);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	bg->Update(V, P);
	player->Update(V, P);	
	collisionsystem->Update(V, P);
}

void Stage2::Render()
{
	bg->Render();
	collisionsystem->Render();
	player->Render();
	
}

