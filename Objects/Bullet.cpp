#include "stdafx.h"
#include "Objects/Bullet.h"
#include "Objects/Player.h"

Bullet::Bullet()
{
	wstring ShaderName = Shaders + L"009_Sprite.fx";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	sprite = new Sprite(
		Textures + L"/Alkanoid/Bullets.png",
		shaderFile,
		334, 695,
		337, 776);

	
	sprite->DrawBound(true);
	sprite->Scale(1.0f, 0.5f);
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
	sprite->Position(position);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position.y += 1;
	sprite->Position(position);
	if (position.y >= Height)
	{
		isValid = false;
	}
}

void Bullet::Render()
{
	sprite->Render();
}


