#include "stdafx.h"
#include "Goliath.h"

#define LEFTARM 0
#define RIGHTARM 1

Goliath::Goliath(D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	wstring texture = Textures + L"/TianSouls/gol_lath.png";
	wstring shader = Shaders + L"/009_Sprite.fx";

	Clip* clip;

	// Head Animation
	{
		// Normal
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(texture, shader, 395, 55, 440, 105), 100000000.0f);
			head->AddClip(clip);
		}

		// Die.
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 8, 15, 57, 64), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 70, 15, 120, 64), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 135, 15, 185, 64), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 200, 15, 250, 64), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 265, 15, 315, 64), 0.3f);
			head->AddClip(clip);
		}
	}
	// body Sprite
	{
		body = new Sprite(texture, shader, 4, 122, 87, 224);
	}	
	// arms aniamtion
	{
		// arm Idle
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 390, 270, 440, 305), 0.3f);
		}

		for (auto a : arms)
		{
			a->AddClip(clip);
		}
		// arm Change Degree
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 390, 270, 440, 305), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 455, 265, 495, 305), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), 0.3f);
		}
		for (auto a : arms)
		{
			a->AddClip(clip);
		}
		// arm Attack
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 330, 260, 375, 295), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), 0.3f);
		}
		for (auto a : arms)
		{
			a->AddClip(clip);
		}
	}

}

Goliath::~Goliath()
{
	for (auto arm : arms)
	{
		SAFE_DELETE(arm);
	}
	SAFE_DELETE(body);
	SAFE_DELETE(head);
}

void Goliath::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
}

void Goliath::Render()
{
}

void Goliath::ApplyDamege(Sprite * sprite)
{
}

Sprite * Goliath::GetSprite()
{
	return nullptr;
}

bool Goliath::IsAttackable()
{
	return false;
}

bool Goliath::IsIdle()
{
	return false;
}
