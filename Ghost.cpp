#include "stdafx.h"
#include "Ghost.h"
#include "Renders/Animation.h"
#include "Objects/Player.h"

extern Player* player;

Ghost::Ghost(D3DXVECTOR2 position) : position(position)
{
	scale = D3DXVECTOR2(1, 1);

	InitializeAnimation();
}

Ghost::~Ghost()
{
}

void Ghost::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
}

void Ghost::Render()
{

}

void Ghost::InitializeAnimation()
{
	animation = new Animation;
	
	wstring spriteFile = Textures + L"/Mario/Enemys.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;

	// IDLE
	{
		// 수정할것.
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9, 87, 51, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73, 87, 115, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 87, 179, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 87, 241, 156), 0.3f);
		animation->AddClip(clip);
	}

	// CHASE
	{

	}

	animation->SetPosition(position);
	animation->SetScale(scale);
	animation->Play(0);

	animation->DrawBound(true);
}
