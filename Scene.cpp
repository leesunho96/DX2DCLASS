#include "stdafx.h"
#include "Device.h"
#include "Player.h"

Player* player;
float speed = 50.0f;
void InitScene()
{
	player = new Player(L"../_Shaders/006_Rect.fx");
	player->Scale(100, 100);

	float x = (float)Width * 0.5f - player->Scale().x * 0.5f;
	float y = player->Scale().y * 0.5f; // 중심 기준 바닥까지 거리가 scale의 절반.

	player->Position(x, y);
}

void DestroyScene()
{
	SAFE_DELETE(player);

}


D3DXMATRIX V, P;
void Update()
{
	if (Key->Press(VK_LEFT))
		player->MoveLeft();
	else if (Key->Press(VK_RIGHT))
		player->MoveRight();

	if (Key->Down(VK_SPACE))
		player->StartJump();
	else if (Key->Up(VK_SPACE))
		player->EndJump();



	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);


	player->Speed(speed);
	player->ViewProjection(V, P);
	player->Update();
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		player->Render();
		ImGui::SliderFloat("500.0f", &speed, 0.0f, 500.0f, "Speed");
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
