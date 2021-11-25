#include "stdafx.h"
#include "Stage1.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"

Stage1::Stage1(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Stage.png", shaderFile);
	backGround->Scale(2.5f, 2.5f);
	backGround->Position(0, 300);

	player = new Player(D3DXVECTOR2(130, 140), D3DXVECTOR2(2.5f, 2.5f));

	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following(player);
}

Stage1::~Stage1()
{
	SAFE_DELETE(player);

	SAFE_DELETE(backGround);
}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	player->Update(V, P);
}

void Stage1::Render()
{
	backGround->Render();

	player->Render();
}