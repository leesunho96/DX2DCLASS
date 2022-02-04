#include "stdafx.h"
#include "CollisionSystem.h"
#include "CollisionDesc.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"
#include "Characters/Player.h"
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
	Update();
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

D3DXVECTOR2 CollisionSystem::GetGoBackVector(Sprite * sprite)
{
	D3DXVECTOR2 result(0.0f, 0.0f);

	for (auto a : collisiondata->line)
	{
		if (a->CollisionTest(sprite))
		{
			float slope = a->GetAngle();

		}
	}
	return result;
}

void CollisionSystem::SetCollisionDesc(CollisionDesc & collisiondesc)
{
	this->collisionDesc.push_back(collisiondesc);
}


// 충돌을 적용할 객체들은 해당 객체에서 collisionDesc 생성 이후, Update시마다 CollisionDesc::SetCollisionDesc() 호출하여 업데이트.
void CollisionSystem::Update()
{


	if (collisionDesc.size() == 0 || collisionDesc.size() == 1)
		return;
	for (size_t i = 0; i < collisionDesc.size() - 1; i++)
	{
		for (size_t j = i + 1; j < collisionDesc.size(); j++)
		{
			if (collisionDesc[i].collisionLayer == collisionDesc[j].collisionLayer)
			{
				if (collisionDesc[i].GetSprite()->OBB(collisionDesc[j].GetSprite()))
				{
					while (collisionDesc[i].GetSprite()->OBB(collisionDesc[j].GetSprite()))
					{
						D3DXVECTOR2 directionVector = collisionDesc[i].GetPosition() - collisionDesc[j].GetPosition();
						D3DXVec2Normalize(&directionVector, &directionVector);
						if (collisionDesc[i].GetPosition() == collisionDesc[j].GetPosition())
						{
							directionVector = D3DXVECTOR2(1, 0);
						}
						float iAlpha = collisionDesc[i].isMoveable ? 0.5f : 0.0f;
						float jAlpha = collisionDesc[j].isMoveable ? 0.5f : 0.0f;
						collisionDesc[i].AdjustPosition(collisionDesc[i].GetPosition() + directionVector * iAlpha);
						collisionDesc[j].AdjustPosition(collisionDesc[j].GetPosition() - directionVector * jAlpha);
					}
				}
			}
		}
	}
	collisionDesc.clear();
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
	GetDistanceBetweenLineAndZeroPosition(data->line);
}

void CollisionSystem::GetInArea(Sprite * sprite)
{

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

vector<bool>& CollisionSystem::GetDistanceBetweenLineAndZeroPosition(vector<Line*> lines)
{
	for (auto a : collisiondata->line)
	{
		if (a->GetDistance(D3DXVECTOR2(0, 0)) > 0)
		{
			bDistanceIsPositive.push_back(true);
		}
		else
		{
			bDistanceIsPositive.push_back(false);
		}
	}
	return bDistanceIsPositive;
}

