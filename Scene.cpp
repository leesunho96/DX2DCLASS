#include "stdafx.h"
#include "Device.h"
#include "myRectDraw.h"

D3DXCOLOR color = D3DXCOLOR(1, 0, 0, 1);

myRectDraw* myrect;
int enemySize = 5;
vector<myRectDraw*> enemyVector;
void InitScene()
{
	myrect = new myRectDraw();
	myrect->setPosition(D3DXVECTOR2(100, 100));
	for (size_t i = 0; i < enemySize; i++)
	{
		enemyVector.push_back((new myRectDraw()));
		enemyVector[i]->setPosition(D3DXVECTOR2(Math::Random(150.0f, 500.0f), Math::Random(150.0f, 500.0f)));
	}
}

void DestroyScene()
{
	delete myrect;
}

D3DXVECTOR2 position = D3DXVECTOR2(100, 100);

void Update()
{
	myrect->setPosition(position);
	myrect->Update();

	RECT temp = enemyVector[0]->GetWorldRect();

	for (auto a : enemyVector)
	{
		a->Update();
	}

}
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::SliderFloat("X", &position.x, 100, Width - 100);
		ImGui::SliderFloat("Y", &position.y, 100, Height - 100);
		myrect->Render();
		for (auto a : enemyVector)
		{
			a->Render();
		}
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
