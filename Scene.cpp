#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Bullet.h"
#include "Objects/Arrow.h"


Arrow* arrow;
Sprite* base;
Background* bg;
Bullet* MAP[10][MAXARRHEIGHT];



void InitScene()
{
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	bg = new Background(shaderFile);
	arrow = new Arrow(
		shaderFile,
		D3DXVECTOR2(Width / 2, 0)
	);
	base = new Sprite
	(
		Textures + L"PuzzleBobble/puzzlebobble.png",
		Shaders + L"008_Sprite.fx",
		25, 1996,
		25 + 65, 2035
	);
	base->Position(Width / 2, 25);

	base->Scale(1.5, 1.5);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			MAP[i][j] = nullptr;
		}
	}

}

void DestroyScene()
{
	SAFE_DELETE(arrow);
	SAFE_DELETE(bg);
	SAFE_DELETE(base);
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

	bg->Update(V, P);
	base->Update(V, P);
	arrow->Update(V, P);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < MAXARRHEIGHT; j++)
		{
			if (MAP[i][j] != nullptr)
			{
				MAP[i][j]->Update(V, P);
			} 
		}
	}


	for (size_t i = 0; i < Bullet::bulletVector.size();)
	{
		if (Bullet::bulletVector[i] == NULL)
		{
			Bullet::bulletVector.erase(Bullet::bulletVector.begin() + i);
		}
		else if (Bullet::bulletVector[i]->getPosition().y < 0)
		{
			SAFE_DELETE(Bullet::bulletVector[i]);
			Bullet::bulletVector[i] = NULL;
		}
		else
		{
			Bullet::bulletVector[i]->setVelocity(-90);
			i++;
		}
	}
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();
		base->Render();
		arrow->Render();
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < MAXARRHEIGHT; j++)
			{
				if (MAP[i][j] != nullptr)
				{
					MAP[i][j]->Render();
				}
			}
		}
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}