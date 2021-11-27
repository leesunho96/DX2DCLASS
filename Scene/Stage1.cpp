#include "stdafx.h"
#include "Stage1.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Viewer/Freedom.h"
#include "Objects/Ball.h"
#include "Objects/Bricks.h"

Player* player;
Ball* ball;

vector<Bricks*> bricksvector;
Stage1::Stage1(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"/Alkanoid/Background.png", shaderFile);
	
	backGround->Scale(1, 1.8);
	D3DXVECTOR2 bgPosition = D3DXVECTOR2(Width / 2, backGround->TextureSize().y / 2);
	backGround->Position(bgPosition);

	player = new Player(D3DXVECTOR2(450, 100), D3DXVECTOR2(1.0f, 1.0f));
	ball = new Ball(shaderFile, D3DXVECTOR2(350, 300), Math::Random(30, 150), 0.2f);




	// 맵 가로 : 220 ~ 580 px
	// 벽돌 하나 크기 : 54 * 22 px
	bricksvector.push_back(new Bricks(0, D3DXVECTOR2(300, 500)));
	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Freedom();
}

Stage1::~Stage1()
{
	SAFE_DELETE(player);
	SAFE_DELETE(ball);
	SAFE_DELETE(backGround);
}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	player->Update(V, P);
	
	for (auto bricks : bricksvector)
	{
		bricks->Update(V, P);
	}

	ball->Update(V, P);
	
}

void Stage1::Render()
{
	backGround->Render();

	player->Render();

	for (auto bricks : bricksvector)
	{
		bricks->Render();
	}

	ball->Render();
}