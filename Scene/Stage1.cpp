#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "Viewer/Freedom.h"
#include "Objects/Player.h"
#include "Objects/Ball.h"
#include "Objects/Bricks.h"
#include "Objects/NonBreakableBricks.h"
#include "Objects/Item.h"
#include "Objects/Bullet.h"
//#include "Systems/MemoryPool.h"

extern Player* player;
extern Ball* ball;
extern ItemMemoryPool* itempool;
extern BulletMemoryPool* bulletpool;
extern vector<IBRICKSINTERFACE*> * pbricksvector;
//extern MemoryPool<Bullet>* bulletPool;

vector<IBRICKSINTERFACE*> bricksvector;
bool istouch = false;
Item* item;

Stage1::Stage1(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"/Alkanoid/Background.png", shaderFile);
	
	backGround->Scale(1, 1.8);
	D3DXVECTOR2 bgPosition = D3DXVECTOR2(Width / 2, backGround->TextureSize().y / 2);
	backGround->Position(bgPosition);

	player = new Player(D3DXVECTOR2(450, 100), D3DXVECTOR2(1.0f, 1.0f));
	ball = new Ball(shaderFile, D3DXVECTOR2(450, 150), Math::Random(30, 150), 0.8f);

	// 아이템 풀 생성
	itempool = new ItemMemoryPool();
	bulletpool = new BulletMemoryPool();
	// bricks pointer setting
	pbricksvector = &bricksvector;

	//for (size_t i = 0; i < 30; i++)
	//{
	//	bulletPool->PushObject(new Bullet());
	//}

	// 맵 가로 : 220 ~ 580 px
	// 벽돌 하나 크기 : 54 * 22 px

	for (size_t i = 0; i < 5; i++)
	{
		bricksvector.push_back(new Bricks(Math::Random(0, 2), D3DXVECTOR2(300 + BRICKSWIDTH * i, 500)));
	}

	for (size_t i = 0; i < 5; i++)
	{
		bricksvector.push_back(new Bricks(Math::Random(0, 2), D3DXVECTOR2(300 + BRICKSWIDTH * i, 500 - BRICKSHEIGHT)));
	}

	for (size_t i = 0; i < 5; i++)
	{
		bricksvector.push_back(new Bricks(Math::Random(0, 2), D3DXVECTOR2(300 + BRICKSWIDTH * i, 500 - BRICKSHEIGHT * 2)));
	}

	for (size_t i = 0; i < 5; i++)
	{
		bricksvector.push_back(new Bricks(Math::Random(0, 2), D3DXVECTOR2(300 + BRICKSWIDTH * i, 500 - BRICKSHEIGHT * 3)));
	}

	//bricksvector.push_back(new NonBreakableBricks(D3DXVECTOR2(300 + BRICKSWIDTH * 3, 300)));
	//bricksvector.push_back(new NonBreakableBricks(D3DXVECTOR2(300 + BRICKSWIDTH * 1, 300)));

	bricksvector.at(0)->SetItem(); 
	bricksvector.at(3)->SetItem();
	bricksvector.at(5)->SetItem();
	bricksvector.at(10)->SetItem();
	bricksvector.at(13)->SetItem();


	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Freedom();
}

Stage1::~Stage1()
{
	for (auto bricks : bricksvector)
	{		
		SAFE_DELETE(bricks);
	}
	//SAFE_DELETE(player);
	SAFE_DELETE(ball);
	SAFE_DELETE(backGround);
	bricksvector.clear();
	pbricksvector = nullptr;
	// 아이템 풀로 객체들 반환.

}

void Stage1::Update()
{
	itempool->CheckItemPool();
	bulletpool->CheckItemPool();

	istouch = false;
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	player->Update(V, P);
	ball->Update(V, P);
	

	itempool->Update(V, P);
	bulletpool->Update(V, P);
	//bulletPool->Update(V, P);

	for (auto bricks : bricksvector)
	{
		if (istouch)
		{
			return;
		}
		bricks->Update(V, P);
	}	
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
	itempool->Render();
	bulletpool->Render();
	//bulletPool->Render();	
}