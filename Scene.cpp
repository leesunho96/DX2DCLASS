#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Bullet.h"
#include "Objects/Arrow.h"

Arrow* arrow;
Sprite* base;

void InitScene()
{
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	arrow = new Arrow(
		shaderFile,
		D3DXVECTOR2(Width / 2, 0)
	);
	base = new Sprite
	(
		Textures + L"PuzzleBobble/puzzlebobble.png",
		Shaders + L"008_Sprite.fx",
		25, 1995,
		25 + 65, 2035
	);
	base->Position(Width / 2, 100);
	//base->Rotation(0.0f);

}

void DestroyScene()
{
	SAFE_DELETE(arrow);
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

	base->Update(V, P);
	arrow->Update(V, P);

	for (auto a : Bullet::bulletvector)
	{
		if (!(a->getIsmoving()) && !(a->isGetRivision))
		{
			a->Position
			(
				D3DXVECTOR2(
				(float)(BaseX + 30 * (a->getArrayList().first)),
				(float)(BaseY - 30 * (a->getArrayList().second))
				)
			);
			a->isGetRivision = true;
		}
		a->Update(V, P);
	}
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		base->Render();
		arrow->Render();
		for (auto a : Bullet::bulletvector)
		{
			a->Render();
		}
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
