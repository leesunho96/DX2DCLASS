#include "stdafx.h"
#include "Goliath.h"
#include "Objects/Goliath_Arm.h"
#include "Objects/Shoulder.h"

#define LEFTARM 0
#define RIGHTARM 1

#define IDLE 0
#define Die 1


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

	{
		shoulders[0] = new Shoulder(ShoulderType::Left, position - D3DXVECTOR2(-body->TextureSize().x * 0.25f, body->TextureSize().y * 0.25f);
		shoulders[1] = new Shoulder(ShoulderType::Right, position - D3DXVECTOR2(body->TextureSize().x * 0.25f, body->TextureSize().y * 0.25f);
	}

	{
		goliathArms[0] = new Goliath_Arm(ArmType::Left, D3DXVECTOR2(-100, 0));
		goliathArms[1] = new Goliath_Arm(ArmType::Left, D3DXVECTOR2(100, 0));
	}

	updateSprites.push_back(bind(&Goliath::UpdateArms, this, placeholders::_1, placeholders::_2));
	updateSprites.push_back(bind(&Goliath::UpdateBody, this, placeholders::_1, placeholders::_2));
	updateSprites.push_back(bind(&Goliath::UpdateHead, this, placeholders::_1, placeholders::_2));
	updateSprites.push_back(bind(&Goliath::UpdateShoulders, this, placeholders::_1, placeholders::_2));

}

Goliath::~Goliath()
{
	for (auto arm : goliathArms)
	{
		SAFE_DELETE(arm);
	}
	for (auto a : shoulders)
	{
		SAFE_DELETE(a);
	}
	SAFE_DELETE(body);
	SAFE_DELETE(head);

}

void Goliath::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	// body, arm, shoulder, head update
	for (auto UpdateSprite : updateSprites)
	{
		UpdateSprite(V, P);
	}
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

void Goliath::UpdateArms(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto arm : goliathArms)
	{
		arm->Update(V, P);
	}
}

void Goliath::UpdateHead(D3DXMATRIX & V, D3DXMATRIX & P)
{
	head->SetPosition(position + D3DXVECTOR2(0, body->TextureSize().y * 0.5f));
	head->SetRotationDegree(rotation);
	head->SetScale(scale);
	head->Update(V, P);
	head->Play(IDLE);
}

void Goliath::UpdateBody(D3DXMATRIX & V, D3DXMATRIX & P)
{
	body->Position(position);
	body->Scale(scale);
	body->RotationDegree(rotation);
	body->Update(V, P);
}

void Goliath::UpdateShoulders(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto shoulder : shoulders)
	{
		shoulder->Update(V, P);
	}
}

