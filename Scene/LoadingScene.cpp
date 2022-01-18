#include "stdafx.h"
#include "LoadingScene.h"
#include "Renders/Sprite.h"


extern bool bIsLoadingFinish;
LoadingScene::LoadingScene(SceneValues * values) : Scene(values)
{
	sprite = new Sprite(Textures + L"TianSouls/TitanSoulsMainSprite.png", Shaders + L"009_Sprite.fx");
	sprite->Scale(1, 1);
	sprite->SetAbsoluteScale(Width, Height);
	sprite->Position(Width * 0.5f, Height * 0.5f);
	sprite->Rotation(0, 0, 0);
}

LoadingScene::~LoadingScene()
{
	SAFE_DELETE(sprite);
}

void LoadingScene::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P;// = values->Projection;

	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	sprite->Update(V, P);
}

void LoadingScene::Render()
{
	sprite->Render();
	DirectWrite::GetDC()->BeginDraw();
	DirectWrite::SetColor(D2D1::ColorF(1, 1, 1));
	{
		wstring text;

		RECT rect;
		rect.left = 330;
		rect.top = 500;
		rect.right = 600;
		rect.bottom = 520;
		text = bIsLoadingFinish ? L"Loading......" : L"Press Enter To Start";

		DirectWrite::RenderText(text, rect);

	}
	DirectWrite::GetDC()->EndDraw();


}
