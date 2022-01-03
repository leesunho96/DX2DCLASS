#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"


Sonic::Sonic(SceneValues * values) : Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
}

Sonic::~Sonic()
{
	for (Marker* marker : markers)
	{
		SAFE_DELETE(marker);
	}
	SAFE_DELETE(backGround);
}

D3DXVECTOR2 mpos;

void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	D3DXVECTOR2 mouse = Mouse->Position();
	
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;
	D3DXVECTOR2 camera = values->MainCamera->GetPosition();
	mpos = mouse + camera;

	if (Mouse->Down(0) == true)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mpos));
	}

	for (Marker* marker : markers)
	{
		marker->Update(V, P);
	}
}

void Sonic::Render()
{
	backGround->Render();
	
	for (Marker* marker : markers)
	{
		marker->Render();
	}

	ImGui::LabelText("MousePosition", "%.0f , %.0f", mpos.x, mpos.y);
}
