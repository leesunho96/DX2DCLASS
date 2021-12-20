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
	ClearMarkersAndLines();
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

	if (markers.size() % 2 == 0)
	{
		while (lines.size() != markers.size() / 2)
		{
			lines.push_back(new Line(markers[lines.size() * 2], markers[lines.size() * 2 + 1]));
		}
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

bool CollisionSystem::CollisionTest(Sprite * sprite)
{
	CollideLineIndexVector.clear();
	bool isColide = false;
	int index = 0;
	for (auto line : lines)
	{
		if (line->CollisionTest(sprite))
		{			
			isColide = true;
			CollideLineIndexVector.push_back(index);
		}
		index++;
	}
	return isColide;
}

float CollisionSystem::GetDegree(Sprite* sprite)
{
	//for (auto line : lines)
	//{
	//	if (line->CollisionTest(sprite))
	//	{
	//		return line->GetAngle();
	//	}
	//}	
	if (CollideLineIndexVector.size() != 0)
	{
		float temp = lines[CollideLineIndexVector[0]]->GetAngle();
		
		if (temp > 90.0f)
		{
			temp = temp - 180.0f;
		}
		else if (temp < -90.0f)
		{
			temp = temp + 180.0f;
		}
		else
			temp = temp;

		return temp;
	}
	return -D3D11_FLOAT32_MAX + 1;
}

void CollisionSystem::PushMarkerByCode(D3DXVECTOR2 Point)
{
	markers.push_back(new Marker(Shaders + L"009_Sprite.fx", Point));

}

void CollisionSystem::PushLineByCode(Line * line)
{
	markers.push_back(line->GetMarker().first);
	markers.push_back(line->GetMarker().second);
	lines.push_back(line);
}

void CollisionSystem::PushCollisionSettingByDesc(LineDesc & desc)
{
	int markersize = desc.Markers.size();
	int linesize = desc.lines.size();

	for (size_t i = 0; i < markersize; i++)
	{
		markers.push_back(desc.Markers[i]);
	}
	for (size_t i = 0; i < linesize; i++)
	{
		lines.push_back(desc.lines[i]);
	}
}

void CollisionSystem::ClearMarkersAndLines()
{
	for (auto a : lines)
	{
		SAFE_DELETE(a);
	}
	for (auto a : markers)
	{
		SAFE_DELETE(a);
	}

	lines.clear();
	markers.clear();
}

vector<float> CollisionSystem::GetDistance(Sprite * input)
{
	vector<float> result;

	for (auto a : lines)
	{
		if (a->CollisionTest(input))
		{
			result.push_back(abs(a->GetDistance(input)));
		}
	}

	return result;
}

bool CollisionSystem::GetIsOnUpperLine(Sprite * sprite)
{
	return GetIsOnUpperLine(sprite->Position());
}

bool CollisionSystem::GetIsOnUpperLine(D3DXVECTOR2 point)
{
	if (lines.size() == 0)
		return false;

	//return lines[CollideLineIndexVector[0]]->GetDistance(point) > 0 ? true : false;
	return lines[0]->GetDistance(point) > 0 ? true : false;
}

