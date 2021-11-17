#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	bgSprite = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx");
	bgSprite->Position(0, 0);
	bgSprite->Scale(2.5, 2.5);
	bgSprite->Rotation(0, 0, 0);
	SetSpriteScaleRotationPosition(bgSprite, D3DXVECTOR2(0, 0));
	Sprite* temp;
	// Ã¹¹ø¤Š ¹Ù´Ú
	temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx", 
		0, 210, 1104 ,240);
	SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(0,240));
	objects.push_back(temp);
	// µÎ¹ø¤Š ¹Ù´Ú
	temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		1135, 210, 1375, 240);
	SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1135, 240));
	objects.push_back(temp);
	// ¼¼¹ø¤Š ¹Ù´Ú
	temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		1424, 210, 2447, 240);
	SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1424, 240));
	objects.push_back(temp);

	temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		2480, 210, 3376, 240);
	SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2480, 240));
	objects.push_back(temp);
}

Background::~Background()
{
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX P)
{

	bgSprite->Update(V, P);
	for (auto sObjects : objects )
	{
		sObjects->Update(V, P);
	}
}
void Background::Render()
{
	bgSprite->Render();
	for (auto sObjects : objects)
	{
		sObjects->Render();
	}
}

void Background::SetSpriteScaleRotationPosition(Sprite * sprite, D3DXVECTOR2 position)
{
	D3DXVECTOR2 adjustPosition = position;
	adjustPosition.x = (position.x + (-(MAPWIDTH * 0.5) + (sprite->TextureSize().x * 0.5))) * 2.5;
	adjustPosition.y = (position.y + (-(MAPHEIGHT * 0.5) + (sprite->TextureSize().y * 0.5))) * 2.5;
	sprite->Rotation(0, 0, 0);
	sprite->Position(adjustPosition);
	sprite->Scale(2.5f, 2.5f);
}
