#include "stdafx.h"
#include "CollisionSystem.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"
#include "Objects/Player.h"
#include "Scene/Scene.h"

#include "Data/LineDesc.h"
#include "Data/CollisionData.h"


CollisionSystem::CollisionSystem(SceneValues * values, Player* player) : scenevalue(values), player(player)
{
}

CollisionSystem::~CollisionSystem()
{	
}

void CollisionSystem::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (Marker* marker : collisiondata->marker)
	{
		marker->Update(V, P);
	}
	for (auto marker : collisiondata->line)
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
		for (Marker* marker : collisiondata->marker)
		{
			marker->Render();
		}
	}

	for (auto marker : collisiondata->line)
	{
		marker->Render();
	}

	//int markersize = collisiondata->marker.size();
	//int LineNum = collisiondata->line.size();
	//ImGui::LabelText("MarkerNum", "%d", markersize);
	//ImGui::LabelText("LineNum", "%d", LineNum);
	
}

bool CollisionSystem::CollisionTest(Sprite * sprite)
{
	CollideLineIndexVector.clear();
	bool isColide = false;
	int index = 0;
	for (auto line : collisiondata->line)
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

bool CollisionSystem::CollisionTest(RECT spritestatus)
{
	CollideLineIndexVector.clear();
	bool isColide = false;
	int index = 0;
	for (auto line : collisiondata->line)
	{
		if (line->CollisionTest(spritestatus))
		{
			isColide = true;
			CollideLineIndexVector.push_back(index);
		}
		index++;
	}
	return isColide;

	return false;
}

float CollisionSystem::GetDegree(Sprite* sprite)
{
	if (CollideLineIndexVector.size() != 0)
	{
		float temp = collisiondata->line[CollideLineIndexVector[0]]->GetAngle();
		
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
	collisiondata->marker.push_back(new Marker(Shaders + L"009_Sprite.fx", Point));

}

void CollisionSystem::PushLineByCode(Line * line)
{
	collisiondata->marker.push_back(line->GetMarker().first);
	collisiondata->marker.push_back(line->GetMarker().second);
	collisiondata->line.push_back(line);
}

void CollisionSystem::PushLineByCode(vector<Line*> line)
{
	for (auto a : line)
	{
		PushLineByCode(a);
	}
}

void CollisionSystem::GetCollisionData(CollisionData * data)
{
	collisiondata = data;
	//for (auto a : data->line)
	//{
	//	collisiondata->line.push_back(a);
	//	collisiondata->marker.push_back(a->GetMarker().first);
	//	collisiondata->marker.push_back(a->GetMarker().second);
	//}
	
}

//void CollisionSystem::PushCollisionSettingByDesc(LineDesc & desc)
//{
//	int markersize = desc.Markers.size();
//	int linesize = desc.collisiondata->line.size();
//
//	for (size_t i = 0; i < markersize; i++)
//	{
//		collisiondata->marker.push_back(desc.Markers[i]);
//	}
//	for (size_t i = 0; i < linesize; i++)
//	{
//		collisiondata->line.push_back(desc.collisiondata->line[i]);
//	}
//}

void CollisionSystem::ClearMarkersAndLines()
{
	for (auto a : collisiondata->line)
	{
		SAFE_DELETE(a);
	}
	for (auto a : collisiondata->marker)
	{
		SAFE_DELETE(a);
	}

	collisiondata->marker.clear();
	collisiondata->line.clear();

}

vector<float> CollisionSystem::GetDistance(Sprite * input)
{
	vector<float> result;

	for (auto a : collisiondata->line)
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
	if (collisiondata->line.size() == 0)
		return false;

	return collisiondata->line[0]->GetDistance(point) > 0 ? true : false;
}

