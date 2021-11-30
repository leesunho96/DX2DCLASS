#include "stdafx.h"
#include "Systems/Device.h"

#include "Objects/Ball.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Scene/Scene.h"
#include "Scene/Stage1.h"
#include "Objects/Item.h"
#include "Objects/IBRICKSINTERFACE.h"
//#include "Systems/MemoryPool.h"


SceneValues* values;
vector<Scene*> scenes;
bool isStop = false;

Player* player;
Ball* ball;
vector<IBRICKSINTERFACE*> * pbricksvector;
ItemMemoryPool* itempool;
//MemoryPool<Bullet>* bulletPool;

void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);
	scenes.push_back(new Stage1(values));
}

void DestroyScene()
{
	for (auto scene : scenes)
	{
		SAFE_DELETE(scene);
	}
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);	
	SAFE_DELETE(itempool);
	//SAFE_DELETE(bulletPool);
}

D3DXMATRIX V, P;
void Update()
{
	//View

	if (!isStop)
	{
		values->MainCamera->Update();

		D3DXMatrixOrthoOffCenterLH(&values->Projection, 0, (float)Width, 0, (float)Height, -1, 1);

		for (Scene* scene : scenes)
		{
			scene->Update();
		}
	}
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (Scene* scene : scenes )
		{
			scene->Render();
		}
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text;

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;
		text = L"Frames per Second : " + std::to_wstring((int)ImGui::GetIO().Framerate);

		DirectWrite::RenderText(text, rect);


		rect.top += 30;
		rect.bottom += 30;
		text = L"Camera Position : " + to_wstring((int)values->MainCamera->GetPosition().x);;
		text += L" , ";
		text += to_wstring((int)values->MainCamera->GetPosition().y);
		DirectWrite::RenderText(text, rect);
	}
	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);
	
}
