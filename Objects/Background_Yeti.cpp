#include "stdafx.h"
#include "Objects/Background_Yeti.h"
#include "Objects/Line.h"
#include "Objects/Marker.h"
#include "Scene/Scene.h"
#include "Physics/CollisionSystem.h"
#include "Systems/CMouse.h"
#include "Data/LineDesc.h"
#include "Data/CollisionData.h"


Background_Yeti::Background_Yeti(SceneValues* scenevalues, float Scale) 
{
	mapSprite = new Sprite(Textures + L"/TianSouls/yeti_map.png", Shaders + L"009_Sprite.fx",
		1704, 983, 2036, 1349);
	mapSprite->SetAbsoluteScale((float)Width * Scale, (float)Height * Scale);

	mapSprite->Position(0, 0);
	mapSprite->Rotation(0, 0, 0);

	{		
		vector<Marker*> markers;																													   
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(0  ,  - 600)) * Scale));			
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(0  ,  - 150)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(70 ,  - 100)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(315,  - 100)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(350,  - 75)) *  Scale) );
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(520,  - 75)) *  Scale) );
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(555,  - 100)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(755,  - 100)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(800,  - 130)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(800,  - 450)) * Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(),  D3DXVECTOR2(600,  - 600)) * Scale));

		vector<Line*> lines;

		for (UINT i = 0; i < markers.size() - 1; i++)
		{
			//mapCollision.lines.push_back(new Line(markers[i], markers[i + 1]));
			lines.push_back(new Line(markers[i], markers[i + 1]));
		}
		//mapCollision.lines.push_back(new Line(markers[0], markers[markers.size() - 1]));		
		lines.push_back(new Line(markers[0], markers[markers.size() - 1]));
		//markers.clear();
		collisiondata = new CollisionData(markers, lines);
	}

}

Background_Yeti::~Background_Yeti()
{
	SAFE_DELETE(mapSprite);
	SAFE_DELETE(collisiondata);
}

void Background_Yeti::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	mapSprite->Update(V, P);
}

void Background_Yeti::Render()
{
	mapSprite->Render();
}
