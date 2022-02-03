#include "stdafx.h"
#include "Background_Goliath.h"
#include "Objects/Line.h"
#include "Objects/Marker.h"
#include "Scene/Scene.h"
#include "Physics/CollisionSystem.h"
#include "Systems/CMouse.h"
#include "Data/LineDesc.h"
#include "Data/CollisionData.h"
#include "Utilities/BinaryFile.h"

Background_Goliath::Background_Goliath(SceneValues * scenevalues, float Scale)
{
	mapSprite = new Sprite(Textures + L"/TianSouls/Go_iath_map.png", Shaders + L"009_Sprite.fx",
		1730, 610, 2095, 920);
	mapSprite->SetAbsoluteScale((float)Width * Scale, (float)Height * Scale);

	mapSprite->Position(0, 0);
	mapSprite->Rotation(0, 0, 0);
	{	
		vector<Marker*> markers;

		if (Path::ExistFile("./SaveFile/GoliathScene.bin"))
		{
			float start = Timer->Running();

			for (auto a : markers)
			{
				SAFE_DELETE(a);
			}
			markers.clear();

			BinaryReader* r = new BinaryReader();
			r->Open(L"./SaveFile/GoliathScene.bin");

			UINT count = r->UInt();

			vector<D3DXVECTOR2> v;
			v.assign(count, D3DXVECTOR2());

			void* ptr = (void*)&(v[0]);
			r->Byte(&ptr, sizeof(D3DXVECTOR2) * count);


			for (UINT i = 0; i < count; i++)
			{
				markers.push_back(new Marker(Shaders + L"009_Sprite.fx", v[i]));
			}

			r->Close();
		}
		/*markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(), (D3DXVECTOR2(0,     0))      - D3DXVECTOR2(0, Height)  )* Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(), (D3DXVECTOR2(Width, 0))      - D3DXVECTOR2(0, Height)  )* Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(), (D3DXVECTOR2(Width, Height - 210)) - D3DXVECTOR2(0, Height)  )* Scale));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", CMouse::GetAdjustPos(scenevalues->MainCamera->GetPosition(), (D3DXVECTOR2(0,     Height - 210)) - D3DXVECTOR2(0, Height)  )* Scale));*/

		vector<Line*> lines;



		for (UINT i = 0; i < markers.size() - 1; i++)
		{
			lines.push_back(new Line(markers[i], markers[i + 1]));
		}
		lines.push_back(new Line(markers[0], markers[markers.size() - 1]));
		collisiondata = new CollisionData(markers, lines);
	}
}

Background_Goliath::~Background_Goliath()
{
	SAFE_DELETE(mapSprite);
	//SAFE_DELETE(collisiondata);
}

void Background_Goliath::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	mapSprite->Update(V, P);
}

void Background_Goliath::Render()
{
	mapSprite->Render();
}
