#include "stdafx.h"
#include "Background_Yeti.h"
#include "Line.h"
#include "Marker.h"
#include "Systems/CollisionSystem.h"


Background_Yeti::Background_Yeti()
{
	mapSprite = new Sprite(Textures + L"/TianSouls/yeti_map.png", Shaders + L"009_Sprite.fx",
		1704, 983, 2036, 1349);
	mapSprite->SetAbsoluteScale((float)Width, (float)Height);
	//mapSprite->Position(Width * 0.5f, Height * 0.5f);
	mapSprite->Position(0, 0);
	mapSprite->Rotation(0, 0, 0);

	{
		LineDesc mapCollision;
		Line* line;
		vector<Marker*> markers;


		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(0, 600)));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(0, 150)));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(70, 100)));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(315, 100)));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(350, 75)));
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(520, 75)));
	}

}

Background_Yeti::~Background_Yeti()
{
	SAFE_DELETE(mapSprite);
}

void Background_Yeti::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	mapSprite->Update(V, P);
}

void Background_Yeti::Render()
{
	mapSprite->Render();
}
