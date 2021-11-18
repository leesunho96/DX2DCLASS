#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	bgSprite = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx");
	bgSprite->Position(0, 0);
	bgSprite->Scale(2.5, 2.5);
	bgSprite->Rotation(0, 0, 0);
	//SetSpriteScaleRotationPosition(bgSprite, D3DXVECTOR2(0, 0));
	Sprite* temp;
	{	// 첫번쨰 바닥
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				0, 210, 1104, 240);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(0, 240));
			objects.push_back(temp);
		}
		// 두번쨰 바닥
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				1135, 210, 1375, 240);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1135, 240));
			objects.push_back(temp);
		}
		// 세번쨰 바닥
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				1424, 210, 2447, 240);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1424, 240));
			objects.push_back(temp);
		}
		//네번째 바닥
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				2480, 210, 3376, 240);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2480, 240));
			objects.push_back(temp);
		}

		for (auto sprites : objects)
		{
			sprites->SetBottom();
		}

	}


	float temppos = 208.0f;
	{
		// 첫번째 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				446, 175, 479, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(446, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

		// 두번째 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				607, 161, 640, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(607, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

		//세번째 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				736, 144, 768, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(736, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

		//네번째 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				912, 144, 943, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(912, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

		// 다섯번째 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				2608, 177, 2639, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2608, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

		// 여섯번쨰 토관
		{
			temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
				2864, 177, 2895, 208);
			SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2864, temppos));
			objects.push_back(temp);
			Pipes.push_back(temp);
		}

	}
	// 첫번쨰 계단
	{
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2145, 193, 2160, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2145, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2160, 175, 2175, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2160, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2175, 160, 2190, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2175, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2190, 145, 2205, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2190, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
	}
	// 두번쨰 계단
	{
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2240, 145, 2255, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2240, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2255, 160, 2270, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2255, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2270, 175, 2285, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2270, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2285, 193, 2300, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2285, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
	}

	// 세번쨰 계단
	{
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2368, 193, 2383, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2368, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2383, 175, 2398, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2398, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2398, 160, 2413, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2398, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2413, 145, 2428, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2413, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			2428, 145, 2443, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2428, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
	}

	// 네번째 계단
	{
		float temppos2 = 2480.0f;
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, 145, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, 160, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, 175, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, 193, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
	}

	{
		float temppos2 = 2895.0f;
		float temppos3 = 192.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;

		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			temppos2, temppos3, temppos2 + 15.0f, 208);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(temppos2, temppos));
		objects.push_back(temp);
		Pipes.push_back(temp);
		temppos2 += 15.0f;
		temppos3 -= 15.0f;
	}

	// 공중 박스들.
	{
		//1
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(320, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//2
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(351, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//3
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(384, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//4
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1231, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//5
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1263, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//6
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1504, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//7
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1599, 160), D3DXVECTOR2(5.0, 2.5));		
		objects.push_back(temp);
		Pipes.push_back(temp);

		//8
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1888, 160));
		objects.push_back(temp);
		Pipes.push_back(temp);

		//9
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(2063, 160), D3DXVECTOR2(5.0, 2.5));		
		objects.push_back(temp);
		Pipes.push_back(temp);

		//10
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1280, 95), D3DXVECTOR2(20.0, 2.5));		
		objects.push_back(temp);
		Pipes.push_back(temp);

		//11
		temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
			320, 145, 335, 160);
		SetSpriteScaleRotationPosition(temp, D3DXVECTOR2(1456, 95), D3DXVECTOR2(7.5, 2.5));		
		objects.push_back(temp);
		Pipes.push_back(temp);

	}
}
Background::~Background()
{
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX P)
{
	bgSprite->Update(V, P);
	for (auto sObjects : objects)
	{
		if (sObjects != nullptr)
		{
			sObjects->Update(V, P);
		}
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

void Background::SetSpriteScaleRotationPosition(Sprite * sprite, D3DXVECTOR2 position, D3DXVECTOR2 Scale)
{
	D3DXVECTOR2 adjustPosition = position;
	adjustPosition.x = (position.x + (-(MAPWIDTH * 0.5) + (sprite->TextureSize().x * 0.5))) * Scale.x;
	adjustPosition.y = (480.0f - position.y + (-(MAPHEIGHT * 0.5) + (sprite->TextureSize().y * 0.5))) * Scale.y;
	sprite->Rotation(0, 0, 0);
	sprite->Position(adjustPosition);
	sprite->Scale(Scale);
}

Sprite* Background::CreateObject(float startX, float startY, float endX, float endY, D3DXVECTOR2 Positon, D3DXVECTOR2 Scale)
{
	Sprite* temp;
	temp = new Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		startX, startY, endX, endY);
	SetSpriteScaleRotationPosition(temp, Positon, Scale);
	objects.push_back(temp);
	return temp;
}
