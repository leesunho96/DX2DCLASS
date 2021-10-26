#include "stdafx.h"
#include "Device.h"
#include "Draws/Rect.h"


Rect* rect;
Rect* rect2;
vector<Rect*> EnemyVector;
int score = 0;

D3DXVECTOR2 position(100, 100);
D3DXMATRIX V, P; // View, P

void InitScene()
{
	rect = new Rect(L"../_Shaders/006_Rect.fx");
	rect->Position(position);
	rect->Scale(100, 100);
	rect->Color(0, 1, 0);
}

// 박스 생성할 때 지정할 랜덤 색상 결정.
D3DXCOLOR GetRandomColor()
{
	D3DXCOLOR colors[] = { D3DXCOLOR(0.0f, 0.0f, 1.0f, 1),
		D3DXCOLOR(0.0f, 1.0f, 0.0f, 1), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1), D3DXCOLOR(1, 0, 0, 1),
		D3DXCOLOR(1, 0, 1, 1), D3DXCOLOR(1, 1, 0, 1) };

	return colors[Math::Random(0, 5)];
}

bool isOverlapBox(Rect& firstBox, Rect& secondBox)
{
	RECT FBOX = firstBox.GetWorldLocation();
	RECT SBOX = secondBox.GetWorldLocation();
	RECT temp;

	return IntersectRect(&temp, &FBOX, &SBOX);
}

void SpawnNewEnemy(vector<Rect*>& EnemyVector)
{
back:
	Rect* tempBox = new Rect(L"../_Shaders/006_Rect.fx",
		D3DXVECTOR2(Math::Random(0.0f, 1000.0f), Math::Random(0.0f, 800.0f)),
		D3DXVECTOR2(Math::Random(100.0f, 150.0f), Math::Random(100.0f, 150.0f))
		, GetRandomColor());

	bool temp = false;


	for (auto a : EnemyVector)
	{
		if (isOverlapBox(*a, *tempBox))
		{
			temp = true;
			break;
		}
	}
	if (temp)
	{
		delete tempBox;
		goto back;
	}
	EnemyVector.push_back(tempBox);
}

void DestroyScene()
{
	SAFE_DELETE(rect);
	SAFE_DELETE(rect2);
}


void CollisionTest(vector<Rect*> &EnemyVector, Rect* player)
{
	for (size_t i = 0; i < EnemyVector.size(); i++)
	{
		if (isOverlapBox(*EnemyVector.at(i), *player))
		{
			Rect* temp = EnemyVector[i];
			EnemyVector.erase(EnemyVector.begin() + i);
			player->Color(temp->Color());
			player->Scale(player->Scale().x + 10.0f, player->Scale().y + 10.0f);
			delete temp;
			score++;
		}
	}

}

void KeyboardInput()
{
	if (Key->Down('W') == true)
	{
		position.y += 10.0f;
	}
	if (Key->Down('A') == true)
	{
		position.x -= 10.0f;
	}
	if (Key->Down('S') == true)
	{
		position.y -= 10.0f;
	}
	if (Key->Down('D') == true)
	{
		position.x += 10.0f;
	}
}
void Update()
{

	KeyboardInput();
	rect->Position(position);

	//View
	D3DXVECTOR3 eye(0, 0, -1); // z : 깊이, 실제 카메라가 보이지 않도록. 화면에서 안보이는 위치. 현재 제작하는 게임은 2d
	D3DXVECTOR3 at(0, 0, 0); // at : 카메라가 바라보는 방향. (0, 0, -1)에서 (0, 0, 0)을 바라봄
	D3DXVECTOR3 up(0, 1, 0); // 상단 방향 알려줌
	D3DXMatrixLookAtLH(&V, &eye, &at, &up); // LeftHanded좌표로 해당 방향 바라봄.

	//projection 세팅
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	rect->ViewProjection(V, P);

	for (auto Enemy : EnemyVector)
	{
		Enemy->ViewProjection(V, P);
	}

	CollisionTest(EnemyVector, rect);
	rect->Update();

}
/*
	그라데이션은 선형보간이루어짐
*/
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::SliderFloat("X", &position.x, 100, Width - 100);
		ImGui::SliderFloat("Y", &position.y, 100, Height - 100);
		ImGui::Text("Score : %d", score);


		if (ImGui::Button("Add"))
		{
			SpawnNewEnemy(EnemyVector);
		}


		rect->Render();

		for (auto Enemy : EnemyVector)
		{
			Enemy->Render();
		}
	}
	// UI는 기존 화면 렌더링 완료 후 그 위에 렌더링.
	ImGui::Render();
	SwapChain->Present(0, 0);
}
