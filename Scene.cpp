#include "stdafx.h"
#include "Systems/Device.h"

vector<Sprite*> sprites;

void InitScene()
{
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	Sprite* mario;
	mario = new Sprite(L"../_Textures/Single.png", shaderFile);
	mario->Position(100, 100);
	sprites.push_back(mario);

	mario = new Sprite(L"../_Textures/All.png", shaderFile, 9, 87, 50, 161);
	mario->Position(300, 300);
	sprites.push_back(mario);



}

void DestroyScene()
{
	for (Sprite* sprite : sprites)
		SAFE_DELETE(sprite);

}

D3DXMATRIX V, P;
void Update()
{
	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	for (Sprite* sprite : sprites)
	{
		sprite->ViewProjection(V, P);
		sprite->Update();
	}


}


int pass = 0;
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (Sprite* sprite : sprites)
			sprite->Render();

	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
