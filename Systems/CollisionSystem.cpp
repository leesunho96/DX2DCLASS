#include "stdafx.h"
#include "CollisionSystem.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"
#include "Scene/Scene.h"

CollisionSystem::CollisionSystem(SceneValues * values) : scenevalue(values)
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 mouse = Mouse->Position();

	mpos = Mouse->GetAdjustPos(scenevalue->MainCamera->GetPosition());
	if (Mouse->DoubleClick(0))
	{
		if (Key->Press(VK_CONTROL))
		{
			markers.push_back(new Marker(Shaders + L"009_Sprite.fx",
				D3DXVECTOR2(mpos.x, markers[markers.size() - 1]->Position().y)));
		}
		else if (Key->Press(VK_MENU))
		{
			markers.push_back(new Marker(Shaders + L"009_Sprite.fx",
				D3DXVECTOR2(markers[markers.size() - 1]->Position().x, mpos.y)));
		}
		else
		{
			markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mpos));
		}
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

void CollisionSystem::Render()
{
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
	ImGui::LabelText("MarkerNum", "%d", markersize);
	ImGui::LabelText("LineNum", "%d", LineNum);
}

void CollisionSystem::CollisionTest(Sprite * sprite)
{
	for (auto line : lines)
	{
		line->CollisionTest(sprite);
	}
}
