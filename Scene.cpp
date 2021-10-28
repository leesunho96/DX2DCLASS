#include "stdafx.h"
#include "Systems/Device.h"
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "Cloud.h"




Player* player;
vector<Ground*> groundVector;
vector<Enemy*> enemyVector;
vector<Cloud*> cloudVector;

void InitScene()
{
	player = new Player(L"../_Shaders/007_Texture.fx", L"../_Textures/Trex/Trex.png", D3DXVECTOR2(100, 50), D3DXVECTOR2(100,100));
	groundVector.push_back(new Ground());
	groundVector.push_back(new Ground(D3DXVECTOR2(((Width / 2) * 3), 10.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus1.png", D3DXVECTOR2(50.0f, 100.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus2.png", D3DXVECTOR2(50.0f, 150.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus3.png", D3DXVECTOR2(50.0f, 150.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus4.png", D3DXVECTOR2(50.0f, 150.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Bird.png", D3DXVECTOR2(50.0f, 50.0f)));
	enemyVector[enemyVector.size() - 1]->setPosition(D3DXVECTOR2(1500, 500));
	cloudVector.push_back(new Cloud(L"../_Textures/Trex/Cloud.png", D3DXVECTOR2(100.0f, 50.0f)));
	cloudVector[0]->setPosition(D3DXVECTOR2(1500, 100));


}

void DestroyScene()
{
	for (auto a : groundVector)
	{
		delete a;
	}

	for (auto a : enemyVector)
	{
		delete a;
	}
	for (auto a : cloudVector)
	{
		delete a;
	}
	delete player;
}


void KeyInput()
{
	if (Key->Down(VK_SPACE))
	{
		player->StartJump();
	}
	else if (Key->Up(VK_SPACE))
	{
		player->EndJump();
	}
}
D3DXMATRIX V, P;
void Update()
{

	player->CollisionTest(enemyVector);

	KeyInput();
	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	player->ViewProjection(V, P);

	player->Update();
	
	for (auto a : groundVector)
	{
		a->ViewProjection(V, P);
		a->Update();
	}

	for (auto a : enemyVector)
	{
		a->ViewProjection(V, P);
		a->Update();
	}

	for (auto a : cloudVector)
	{
		a->ViewProjection(V, P);
		a ->Update();
	}
}

int pass = 0;
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		player->Render();
		
		for (auto a : groundVector)
		{
			a->Render();
		}
		for (auto a : enemyVector)
		{
			a->Render();
		}
		for (auto a : cloudVector)
		{
			a->Render();
		}

		ImGui::Text("Death Count : %d", player->deathCount);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
