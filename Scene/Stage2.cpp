#include "stdafx.h"
#include "Stage2.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Viewer/Freedom.h"
#include "Objects/Background_Yeti.h"


Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	bg = new Background_Yeti();
	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
	
}

Stage2::~Stage2()
{
	SAFE_DELETE(bg);
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	bg->Update(V, P);

}

void Stage2::Render()
{
	bg->Render();
}

