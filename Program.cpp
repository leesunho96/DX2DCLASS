#include "stdafx.h"
#include "Systems/Device.h"

#include "Objects/Bullet.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Scene/Scene.h"
#include "Scene/Stage2.h"


SceneValues* values;
vector<Scene*> scenes;


void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	//scenes.push_back(new Stage2(values));
	scenes.push_back(new Stage2(values));
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


		//	D3DXMatrixOrthoOffCenterLH(&values->Projection, 
		//	0, (float)Width, 
		//	0, (float)Height,
		//	-1, 1 // z축
		//);

		D3DXMatrixOrthoOffCenterLH(&values->Projection, 
			-(float)Width * 0.5f, (float)Width * 0.5f, 
			-(float)Height * 0.5f, (float)Height * 0.5f,
			-1, 1 // z축
		);

	//D3DXMatrixOrthoOffCenterLH(&values->Projection,
	//	horizental.x, horizental.y,
	//	vertical.x, vertical.y,
	//	-1, 1 // z축
	//);



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
		ImGui::SliderFloat2("Horizental", (float*)&horizental, -1000, 1000);
		ImGui::SliderFloat2("Vertical", (float*)&vertical, -1000, 1000);

		for (Scene* scene : scenes)
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

		rect.top += 30;
		rect.bottom += 30;
		text = L"Mouse Position : " + to_wstring((int)Mouse->Position().x);
		text += L" , ";
		text += to_wstring((int)Mouse->Position().y);
		DirectWrite::RenderText(text, rect);
	}

	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);
}
