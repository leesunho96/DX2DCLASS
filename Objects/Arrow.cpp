#include "stdafx.h"
#include "Arrow.h"
#include "Draws/Sprite.h"
#include "Objects/Bullet.h"

Bullet* tempBullet = nullptr;

void Arrow::Initialize(wstring shaderFile, D3DXVECTOR2 start)
{

	float startX = 92.0f;
	float startY = 1735.0f;
	float width = 65.0f;
	Arrows = new Sprite
	(
		Textures + L"PuzzleBobble/puzzlebobble.png",
		Shaders + L"008_Sprite.fx",
		startX, startY,
		startX + width, startY + width
	);

	vPosition = start;
	Arrows->Scale(1.5, 1.5);
	fangle = 90.0f;
	Arrows->Position(vPosition);
	Arrows->Rotation(fangle - 90);
	vRadius = GetRadius(fangle);
	tempBullet = new Bullet(
		Shaders + L"008_Sprite.fx",
		baseBulletPosition,
		fangle,
		1.0f);
}

Arrow::Arrow(wstring shaderFile, D3DXVECTOR2 start)
{
	Initialize(shaderFile, start);
}

void Arrow::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (tempBullet == nullptr)
	{
		tempBullet = new Bullet(
			Shaders + L"008_Sprite.fx",
			baseBulletPosition,
			fangle,
			1.0f);
	}

	float size = 0.01f;
	if (Key->Press(VK_RIGHT))
	{
		if(fangle - size > 30.0f)
			fangle -= size;
	}
	if (Key->Press(VK_LEFT))
	{
		if(fangle + size < 150.0f)
			fangle += size;
	}
	if (Key->Down(VK_SPACE))
	{
		if (!tempBullet->getIsmoving())
		{
			tempBullet->setVelocity(fangle);
		}

	}
	Arrows->Rotation(fangle - 90.0f);
	Arrows->Position(vPosition);
	Arrows->Update(V, P);
	if (tempBullet != nullptr)
	{
		if (!tempBullet->getIsmoving())
			tempBullet->Position(GetBaseBulletLocation());
		tempBullet->Update(V, P);
	}
}

void Arrow::Render()
{
	Arrows->Render();
	if(tempBullet!=nullptr)
		tempBullet->Render();
}

Arrow::~Arrow()
{
}

D3DXVECTOR2 Arrow::GetRadius(float angle)
{
	return D3DXVECTOR2(cosf(angle), sinf(angle));
}

D3DXVECTOR2 Arrow::GetBaseBulletLocation()
{
	D3DXVECTOR2 temp(
		baseBulletPosition.x,
		baseBulletPosition.y
	);

	return temp;
}


