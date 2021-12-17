#include "stdafx.h"
#include "Background_Yeti.h"

Background_Yeti::Background_Yeti()
{
	mapSprite = new Sprite(Textures + L"/TianSouls/yeti_map.png", Shaders + L"009_Sprite.fx",
		1704, 983, 2036, 1349);
	mapSprite->SetAbsoluteScale((float)Width, (float)Height);
	//mapSprite->Position(Width * 0.5f, Height * 0.5f);
	mapSprite->Position(0, 0);
	mapSprite->Rotation(0, 0, 0);
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
