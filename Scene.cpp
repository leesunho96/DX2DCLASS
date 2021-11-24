#include "stdafx.h"
#include "Systems/Device.h"

#include "Objects/Bullet.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"

Player* player;
Sprite* sprite;

Camera* camera;

void InitScene()
{
	player = new Player(D3DXVECTOR2(100, 170), D3DXVECTOR2(2.5f, 2.5f));
	sprite = new Sprite(Textures + L"Stage.png", Shaders + L"009_Sprite.fx");
	//camera = new Freedom();
	camera = new Following(player);
}

void DestroyScene()
{
	SAFE_DELETE(camera)
	SAFE_DELETE(sprite);
	SAFE_DELETE(player);

}

D3DXMATRIX V, P;
void Update()
{
	//View
	camera->Update();
	V = camera->GetView();
	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	player->Update(V, P);
	sprite->Rotation(0, 0, 0);
	sprite->Scale(2.5f, 2.5f);
	sprite->Position(0, 300);
	sprite->Update(V, P);

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::LabelText("FPS", "%.0f", ImGui::GetIO().Framerate);
		camera->Render();
		sprite->Render();
		player->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"에러를 잡자";

		RECT rect;
		rect.left = 20.0f;
		rect.top = 20.0f;
		rect.right = 1000.0f;
		rect.bottom = 40.0f;

		DirectWrite::RenderText(text, rect);

		int temp = (int)ImGui::GetIO().Framerate;
		text = std::to_wstring(temp);
		rect.top += 30;
		rect.bottom += 30;

		DirectWrite::RenderText(text, rect);
	}

	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);
}
