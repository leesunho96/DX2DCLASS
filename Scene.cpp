#include "stdafx.h"
#include "Device.h"
#include "myRectDraw.h"

D3DXCOLOR color = D3DXCOLOR(1, 0, 0, 1);

myRectDraw* myrect;
void InitScene()
{
	myrect = new myRectDraw();
	myrect->setPosition(D3DXVECTOR2(100, 100));

}

void DestroyScene()
{
	delete myrect;
}

D3DXVECTOR2 position = D3DXVECTOR2(100, 100);
D3DXVECTOR2 position2 = D3DXVECTOR2(100, 100);

void Update()
{
	myrect->setPosition(position);
	myrect->Update();
}
/*
	�׶��̼��� ���������̷����
*/
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::SliderFloat("X", &position.x, 100, Width - 100);
		ImGui::SliderFloat("Y", &position.y, 100, Height - 100);
		myrect->Render();
	}
	// UI�� ���� ȭ�� ������ �Ϸ� �� �� ���� ������.
	ImGui::Render();
	SwapChain->Present(0, 0);
}
