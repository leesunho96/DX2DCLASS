#include "stdafx.h"
#include "Systems/Device.h"
#include "Physics/CollisionSystem.h"

#include "Objects/Bullet.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"
#include "Scene/Scene.h"
#include "Scene/Stage2.h"
#include "Scene/LoadingScene.h"
#include <thread>

SceneValues* values;
vector<Scene*> scenes;
CollisionSystem* collisionsystem;
bool bIsDebugging = true;
bool bIsLoadingFinish = false;
vector<Scene*> loadingScene;
vector<Scene*> waitingScene;
thread* t1;


void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);
		
	scenes.push_back(new LoadingScene(values));;
	t1 = new thread([]() { loadingScene.push_back(new Stage2(values)); bIsLoadingFinish = true; });
	
}

void DestroyScene()
{
	for (auto scene : scenes)
	{
		SAFE_DELETE(scene);
	}
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
}

D3DXVECTOR2 horizental(0, 800), vertical(0, 600);

D3DXMATRIX V, P;
void Update()
{
	//View

	values->MainCamera->Update();

	// OrthoGraphy : 직교
	// Perspective : 원근

	/*	2 / (r - l)			0                 0                0
		0					2 / (t - b)       0                0
		0					0                 1 / (zf - zn)    0
		(l + r) / (l - r)  (t + b) / (b - t)  zn / (zn - zf)   1
		r : right, l = left => r - l : 길이
		t : top, b : bottom => t-b : 높이
		f : far, z : near
		(4,4)=> 1 :: z축 기준 가까운 면만 렌더링하니까 1.

		(l+r) / (l-r) => -1.
		*/


		D3DXMatrixOrthoOffCenterLH(&values->Projection, 
			-(float)Width * 0.5f, (float)Width * 0.5f, 
			-(float)Height * 0.5f, (float)Height * 0.5f,
			-1, 1 // z축
		);

	//if (bIsLoadingFinish && Key->Down(VK_END))
	//{
	//	bIsLoadingFinish = false;
	//	for (auto scene : scenes)
	//	{
	//		waitingScene.push_back(scene);
	//	}
	//	scenes.clear();
	//	scenes.push_back(loadingScene[0]);
	//	loadingScene.clear();
	//}

	// 원근 투영
	//D3DXMatrixPerspectiveOffCenterLH(&values->Projection, 0, (float)Width, 0, (float)Height, -1, 1);
	for (Scene* scene : scenes)
	{
		scene->Update();
	}
	
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 0);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (Scene* scene : scenes)
		{
			scene->Render();
		}
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	DirectWrite::SetColor(D2D1::ColorF(0, 0, 0));
	{
		wstring text;

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;
		text = L"Frames per Second : " + std::to_wstring((int)ImGui::GetIO().Framerate);

		DirectWrite::RenderText(text, rect);

	}
	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);

	//if (bIsLoadingFinish && Key->Down(VK_END))
	//{
	//	bIsLoadingFinish = false;
	//	for (auto scene : scenes)
	//	{
	//		waitingScene.push_back(scene);
	//	}
	//	scenes.clear();
	//	scenes.push_back(loadingScene[0]);
	//	loadingScene.clear();
	//}

	if (t1->joinable())
	{
		t1->join();
		scenes.at(0) = loadingScene.at(0);
	}


}
