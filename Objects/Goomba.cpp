#include "stdafx.h"
#include "Goomba.h"
#include "Player.h"

extern Player* player;

Goomba::Goomba(float fStartXpos, float fEndXPos)
{
	this->fStartXpos = fStartXpos;
	this->fEndXpos = fEndXPos;
	animation = new Animation;

	wstring spriteFile = Textures + L"/Mario/Goomba.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";


	Clip* clip;

	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 116, 42, 281, 202), 0.5f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 330, 42, 490, 202), 0.5f);

	}
	animation->AddClip(clip);

	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 540, 100, 703, 181), 1.0f);
	}
	animation->AddClip(clip);
	position.x = (fStartXpos + fEndXPos) * 0.5f;
	position.y = 100.0f;
	animation->SetPosition(position);
	animation->SetScale(0.3f, 0.3f);
	animation->Play(0);
}

Goomba::~Goomba()
{
}

void Goomba::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	int setClip;

	position = animation->GetPosition();

	if (isToRight)
	{
		position.x += 0.1f;
		isToRight = position.x >= fEndXpos ? false : true;
	}
	else
	{
		position.x -= 0.1f;
		isToRight = position.x <= fStartXpos ? true : false;
	}

	if (isOverlap)
	{
		elapseTime += Timer->Elapsed();
	}

	RECT PlayerLocation = player->GetWorldLocation();
	RECT GoombaLocation = animation->GetWorldLocation();
	if (PlayerLocation.right > fStartXpos &&
		PlayerLocation.left < fEndXpos)
	{
		RECT temp;
		if (IntersectRect(&temp, &PlayerLocation, &GoombaLocation))
		{
			if ((PlayerLocation.top <= GoombaLocation.bottom + 1.0f) &&  
				(PlayerLocation.left + PlayerLocation.right) * 0.5f > GoombaLocation.left - 10.0f
				&& (PlayerLocation.left + PlayerLocation.right) * 0.5f < GoombaLocation.right + 10.0f)
			{
				isOverlap = true;
				player->SetVelocity();
			}
			else if ((PlayerLocation.left + PlayerLocation.right) * 0.5f <= GoombaLocation.right - 10.0f ||
				(PlayerLocation.left + PlayerLocation.right) * 0.5f >= GoombaLocation.left + 10.0f)
			{
				player->ApplyDamege();
				
			}

		}
		else
		{
			
		}
	}
	else
	{
		
	}

	if (isOverlap)
	{
		if (elapseTime >= 1.0f)
		{
			isOverlap = false;
			elapseTime = 0.0f;
			setClip = 0;
		}
		else
		{
			setClip = 1;
		}
	}
	else
	{
		setClip = 0;
		isOverlap = false;
	}

	animation->SetPosition(position);
	animation->Play(setClip);
	animation->Update(V, P);
}

void Goomba::Render()
{
	animation->Render();
}

void Goomba::ApplyDamege()
{
}
