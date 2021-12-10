#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"

vector<Marker*> *markerpointer = nullptr;


Sonic::Sonic(SceneValues * values) : Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
	markerpointer = &markers;

	markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(0, 0)));
	markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(10, 10)));
	lines.push_back(new Line(markers[0], markers[1]));
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
	

	mpos = Mouse->GetAdjustPos(values->MainCamera->GetPosition());

	if (Mouse->DoubleClick(0))
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mpos));
	}

	if (markers.size() % 2 == 0 && lines.size() != markers.size() / 2)
	{
		lines.push_back(new Line(markers[markers.size() - 1], markers[markers.size() - 2]));
	}
	for (Marker* marker : markers)
	{
		marker->Update(V, P);
	}
	for (auto marker : lines)
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

	for (auto marker : lines)
	{
		marker->Render();
	}

	int markersize = markers.size();
	int LineNum = lines.size();
	ImGui::LabelText("MousePosition", "%.0f , %.0f", mpos.x, mpos.y);
	ImGui::LabelText("MarkerNum", "%d", markersize);
	ImGui::LabelText("LineNum", "%d", LineNum);
}
