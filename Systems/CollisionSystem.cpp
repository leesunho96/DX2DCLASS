#include "stdafx.h"
#include "CollisionSystem.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"
#include "Scene/Scene.h"
#include "Objects/Player.h"

CollisionSystem::CollisionSystem(SceneValues * values, Player* player) : scenevalue(values), player(player)
{
}

CollisionSystem::~CollisionSystem()
{
	for (auto marker : markers)
	{
		SAFE_DELETE(marker);
	}
	for (auto line : lines)
	{
		SAFE_DELETE(line);
	}
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
	if (ImGui::Button(bIsRenderMarker ? "Remove Marker" : "Render Marker"))
	{
		bIsRenderMarker =  bIsRenderMarker ? false : true;
	}
	if (bIsRenderMarker)
	{
		for (Marker* marker : markers)
		{
			marker->Render();
		}
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
	bool isColide = false;
	for (auto line : lines)
	{
		if (line->CollisionTest(sprite))
		{
			player->SetDegree(line->GetAngle());
			isColide = true;
		}
	}

	player->SetBOnGround(isColide);
}

float CollisionSystem::GetDegree(Sprite* sprite)
{
	for (auto line : lines)
	{
		if (line->CollisionTest(sprite))
		{
			return line->GetAngle();
		}
	}
	return -D3D11_FLOAT32_MAX + 1;
}
