#include "stdafx.h"
#include "Arrow.h"
#include "Draws/Sprite.h"
#include "Objects/Bullet.h"

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
	Arrows->Scale(1, 1);
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
	int size = 1.0f;
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
		tempBullet->setVelocity(fangle);
		Bullet::bulletvector.push_back(tempBullet);



		tempBullet = new Bullet(
			Shaders + L"008_Sprite.fx",
			baseBulletPosition,
			fangle,
			1.0f);
	}

	Arrows->Rotation(fangle - 90);
	Arrows->Position(vPosition);
	Arrows->Update(V, P);
	for (auto a : bullets)
	{
		a->Update(V, P);
	}
	if(!tempBullet->getIsmoving())
		tempBullet->Position(GetBaseBulletLocation());
	tempBullet->Update(V, P);
}

void Arrow::Render()
{
	for (auto a : bullets)
	{
		a->Render();
	}
	Arrows->Render();
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
		baseBulletPosition.x - 30 * sinf(Math::ToDegree(fangle - 90)),
		baseBulletPosition.y - 30 * cosf(Math::ToDegree(fangle - 90))
	);

	return temp;
}


