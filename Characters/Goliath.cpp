#include "stdafx.h"
#include "Goliath.h"
#include "Objects/Goliath_Arm.h"
#include "Objects/Shoulder.h"

#define LEFTARM 0
#define RIGHTARM 1

#define IDLE 0
#define ACTIVATE 1
#define Die 2


Goliath::Goliath(D3DXVECTOR2 position, D3DXVECTOR2 scale) : scale(scale), position(position), PresentState(IDLE)
{
	wstring texture = Textures + L"/TianSouls/gol_lath.png";
	wstring shader = Shaders + L"/009_Sprite.fx";

	Clip* clip;
	head = new Animation();
	// Head Animation
	{
		// Activate
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(texture, shader, 395, 55, 445, 105), 100000000.0f);
			head->AddClip(clip);
		}
		// Idle
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(texture, shader, 8, 15, 57, 64),    0.2f);
			clip->AddFrame(new Sprite(texture, shader, 70, 15, 120, 64),  0.2f);
			clip->AddFrame(new Sprite(texture, shader, 135, 15, 185, 64), 0.2f);
			clip->AddFrame(new Sprite(texture, shader, 200, 15, 250, 64), 0.2f);
			clip->AddFrame(new Sprite(texture, shader, 265, 15, 315, 64), 0.2f);
			head->AddClip(clip);
		}
		// Die.
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(texture, shader, 8, 15, 57, 64),    0.1f);
			clip->AddFrame(new Sprite(texture, shader, 70, 15, 120, 64),  0.1f);
			clip->AddFrame(new Sprite(texture, shader, 135, 15, 185, 64), 0.1f);
			clip->AddFrame(new Sprite(texture, shader, 200, 15, 250, 64), 0.1f);
			clip->AddFrame(new Sprite(texture, shader, 265, 15, 315, 64), 0.1f);
			head->AddClip(clip);
		}
	}
	// body Sprite
	{
		body = new Sprite(texture, shader, 4, 122, 87, 224);
	}	

	{
		shoulders[0] = new Shoulder(ShoulderType::Left, position + D3DXVECTOR2(-body->TextureSize().x * 0.75f, body->TextureSize().y * 0.35f), scale);
		shoulders[1] = new Shoulder(ShoulderType::Right, position + D3DXVECTOR2(body->TextureSize().x * 0.75f, body->TextureSize().y * 0.35f), scale);
	}

	{
		goliathArms[0] = new Goliath_Arm(ArmType::Left,  position + D3DXVECTOR2(-body->TextureSize().x, -body->TextureSize().y) * 0.75f, scale);
		goliathArms[1] = new Goliath_Arm(ArmType::Right, position + D3DXVECTOR2( body->TextureSize().x, -body->TextureSize().y) * 0.75f, scale);
	}

	updateSprites.push_back(bind(&Goliath::UpdateBody, this, placeholders::_1, placeholders::_2));
	updateSprites.push_back(bind(&Goliath::UpdateArms, this, placeholders::_1, placeholders::_2));
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
	sprites.clear();
	// body, arm, shoulder, head update
	for (auto UpdateSprite : updateSprites)
	{
		UpdateSprite(V, P);
	}
}

void Goliath::Render()
{
	body->Render();
	shoulders[0]->Render();
	shoulders[1]->Render();
	head->Render();
	goliathArms[0]->Render();
	goliathArms[1]->Render();
}

void Goliath::ApplyDamege(Sprite * sprite)
{
	switch (PresentState)
	{
	case IDLE:
		PresentState = ACTIVATE;
		for (auto shoulder : shoulders)
		{
			shoulder->SetActivate();
		}
		break;
	case ACTIVATE:
		PresentState = Die;
		for (auto shoulder : shoulders)
		{
			shoulder->SetDeactivate();
		}
		break;
	case Die:
		break;

	default:
		break;
	}

}


bool Goliath::IsAttackable()
{
	return PresentState != IDLE;
}

bool Goliath::IsIdle()
{
	return PresentState == IDLE;
}

void Goliath::UpdateArms(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto arm : goliathArms)
	{
		sprites.push_back(arm->GetSprite());
		arm->Update(V, P);
	}
}

void Goliath::UpdateHead(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (PresentState == IDLE || PresentState == ACTIVATE)
	{
		head->Play(PresentState);
		sprites.push_back(head->GetSprite());
		head->SetPosition(position + D3DXVECTOR2(0, body->TextureSize().y * 0.6f));
		head->SetRotationDegree(rotation);
		head->SetScale(scale);
		head->Update(V, P);
	}
	else
	{
		head->Play(Die);
		sprites.push_back(head->GetSprite());
		head->SetPosition(position + D3DXVECTOR2(0, body->TextureSize().y * 0.6f) - D3DXVECTOR2(100,-100) * Timer->Elapsed());
		head->SetRotationDegree(rotation);
		head->SetScale(scale);
		head->Update(V, P);
	}
}

void Goliath::UpdateBody(D3DXMATRIX & V, D3DXMATRIX & P)
{
	sprites.push_back(body);
	body->Position(position);
	body->Scale(scale);
	body->RotationDegree(rotation);
	body->Update(V, P);
}

void Goliath::UpdateShoulders(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto shoulder : shoulders)
	{
		sprites.push_back(shoulder->GetSprite());
		shoulder->Update(V, P);
	}
}

