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

bool bIsGameOn = true;
int score = 0;
int maxScore = 0;
/*
	플레이어를 초기화하는 메소드.
	게임 시작, 게임 재시작 할 떄 호출될 것.
*/
void createPlayer()
{
	player = new Player(L"../_Shaders/007_Texture.fx", L"../_Textures/Trex/Trex.png", 
		D3DXVECTOR2(100, 50), D3DXVECTOR2(100, 100));
}
// 플레이어 삭제 메소드. 게임 종료시만 호출됨
void DeletePlayer()
{
	SAFE_DELETE(player);
}
// 적 생성하는 메소드. 적이랑 바닥, 구름 생성.
// 게임 시작시, 적과 부딛혀서 게임 재시작시 생성.
void createEnemys()
{
	groundVector.push_back(new Ground());
	groundVector.push_back(new Ground(D3DXVECTOR2(((Width / 2) * 3), 10.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus1.png", D3DXVECTOR2(35.0f, 50.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus2.png", D3DXVECTOR2(35.0f, 100.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus3.png", D3DXVECTOR2(35.0f, 100.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Cactus4.png", D3DXVECTOR2(35.0f, 100.0f)));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Bird.png", D3DXVECTOR2(50.0f, 30.0f)));
	enemyVector[enemyVector.size() - 1]->setPosition(D3DXVECTOR2(Math::Random(1500.0f, 3000.0f), 150));
	enemyVector.push_back(new Enemy(L"../_Textures/Trex/Bird.png", D3DXVECTOR2(50.0f, 30.0f)));
	enemyVector[enemyVector.size() - 1]->setPosition(D3DXVECTOR2(Math::Random(2000.0f, 5000.0f), 300));

	cloudVector.push_back(new Cloud(L"../_Textures/Trex/Cloud.png", D3DXVECTOR2(100.0f, 50.0f)));
	cloudVector[0]->setPosition(D3DXVECTOR2(1500, 100));
	cloudVector.push_back(new Cloud(L"../_Textures/Trex/Cloud.png", D3DXVECTOR2(100.0f, 50.0f)));
	cloudVector[1]->setPosition(D3DXVECTOR2(2000, 300));
	bIsGameOn = true;
}

// 적 삭제 메소드. 게임 종료시와 적과 부딛힌 순간 호출된다.
void DeleteEnemys()
{
	for (auto a : groundVector)
	{
		SAFE_DELETE(a);
	}
	for (auto a : enemyVector)
	{
		SAFE_DELETE(a);
	}
	for (auto a : cloudVector)
	{
		SAFE_DELETE(a);
	}
	groundVector.clear();
	enemyVector.clear();
	cloudVector.clear();
	bIsGameOn = false;
}

// 게임 생성 메소드, 플레이어와 적 동시에 생성. InitScene에서만 호출
void CreateGame()
{
	createPlayer();
	createEnemys();
}

// 게임 삭제 메소드. deleteScene에서만 호출.
void DeleteGame()
{
	DeleteEnemys();
	DeletePlayer();
}
// 점수 초기화 메소드. 적과 부딛혀서 점수 초기화 할 떄만 호출.
void resetScore()
{
	score = 0;
}

// 키 입력 메소드.
// 키 입력 후, 처리까지 수행. 
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
	if (Key->Press(VK_DOWN))
	{
		player->SetCrouch();
	}
}

// update 시 호출, 각 벡터 내 객체들에 V, P 세팅
void SetViewProjection()
{
	D3DXMATRIX V, P;
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	

	player->Update(V, P);

	for (auto a : groundVector)
	{
		//a->ViewProjection(V, P);
		a->Update(V, P);
	}

	for (auto a : enemyVector)
	{
		//a->ViewProjection(V, P);
		a->Update(V, P);
	}

	for (auto a : cloudVector)
	{
		//a->ViewProjection(V, P);
		a->Update(V, P);
	}
}

int pass = 0;
// render시 호출, 각 벡터 내 객체들 렌더링.
void RenderObjects()
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
}


void checkRanking()
{
	maxScore = maxScore < score ? score : maxScore;
}

////////////////////////////////////////////////////////////////////////////
//// MAIN////////////////////////////////////////////////////
void InitScene()
{
	CreateGame();
}
void DestroyScene()
{
	DeleteGame();
}
void Update()
{
	KeyInput();
	if (player->CollisionTest(enemyVector))
	{
		DeleteEnemys();
		checkRanking();
	}
	SetViewProjection();
	if (bIsGameOn)
	{
		score++;
	}
}
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		RenderObjects();
		ImGui::Text("Death Count : %d", player->deathCount);
		ImGui::Text("Score : %d", score);
		ImGui::Text("MaxScore : %d", maxScore);
		ImGui::Text("Player Y : %d", player->Position().y);
		if (!bIsGameOn)
		{
			ImGui::Text("Game Over");
			if (ImGui::Button("RESTART"))
			{
				createEnemys();
				resetScore();
				player->ResetClip();
				player->SetPlaying();
			}
		}

	}
	ImGui::Render();
	SwapChain->Present(0, 0);

}
