#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"

void Player::InitializeClip(std::wstring &shaderFile)
{
	wstring spriteFile = Textures + L"Trex/TrexImages.png";

	Walk = new Clip(
		PlayMode::Loop, 0.5f
	);
	Jump = new Clip(
		PlayMode::Loop, 0.5f
	);
	Die = new Clip(
		PlayMode::Loop, 0.5f
	);
	Crouch = new Clip(
		PlayMode::Loop, 0.5f
	);

	Walk->AddFrame(new Sprite(
		spriteFile, shaderFile,
		936, 2, 980, 49), 0.5f);
	Walk->AddFrame(new Sprite(
		spriteFile, shaderFile,
		980, 2, 1024, 49), 0.5f);
	Jump->AddFrame(new Sprite(
		spriteFile, shaderFile,
		848, 2, 892, 49), 0.5f);
	Jump->AddFrame(new Sprite(
		spriteFile, shaderFile,
		892, 2, 936, 49), 0.5f);
	Crouch->AddFrame(new Sprite(
		spriteFile, shaderFile,
		1112, 2, 1171, 49), 0.5f);
	Crouch->AddFrame(new Sprite(
		spriteFile, shaderFile,
		1171, 2, 1230, 49), 0.5f);
	Die->AddFrame(new Sprite(
		spriteFile, shaderFile,
		1024, 2, 1068, 49), 0.5f);
	Die->AddFrame(new Sprite(
		spriteFile, shaderFile,
		1068, 2, 1112, 49), 0.5f);
	PresentClip = Walk;
	Walk->Position(Position());
	Walk->Scale(100.0f, 100.0f);

	Jump->Position(Position());
	Jump->Scale(100.0f, 100.0f);

	Die->Position(Position());
	Die->Scale(100.0f, 100.0f);

	Crouch->Position(Position());
	Crouch->Scale(100.0f, 100.0f);

	Walk->Play();
	Jump->Play();
	Die->Play();
	Crouch->Play();
}


Player::Player(wstring shaderFile, wstring imgFile) : 
	Rect(shaderFile, imgFile),
speed(50.0f), velocity(0.0f), 
gravity(-0.5f), bOnGround(true)
{
	InitializeClip(shaderFile);
}

Player::Player(wstring shaderFile, wstring imgFile, D3DXVECTOR2 position, D3DXVECTOR2 scale)
	: Rect(shaderFile, imgFile, position, scale),
	speed(50.0f), velocity(0.0f), gravity(-0.0003f), bOnGround(true)
{
	InitializeClip(shaderFile);
}

Player::~Player()
{
}

void Player::ResetClip()
{
	PresentClip = Walk;
}

void Player::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	//__super::Update(); // 상위 클래스 Update 먼저 호출.
	D3DXVECTOR2 position = Position();
	velocity += gravity; // Time::Delta : 컴퓨터마다 속도가 다름. 해당 속도는 달라도 간격은 동일. 해당값을 보정하기 위함. 서버 렉 통신 관련 문제 해결.

	if (bIsPlaying)
	{
		if (bOnGround == false)
		{
			position.y += velocity;
			Position(position);
		}

		if (Position().y > 51)
		{
			PresentClip = Jump;
		}
		if (position.y < Scale().y * 0.5f)
		{
			position.y = Scale().y * 0.5f;
			velocity = 0.0f;
			bOnGround = true;
			presentJump = 0;
			Position(position);
			PresentClip = Walk;
		}
	}
	Walk->Position(position);
	Walk->Update(V, P);
	
	Jump->Position(position);
	Jump->Update(V, P);
	
	Die->Position(position);
	Die->Update(V, P);

	Crouch->Position(position);
	Crouch->Update(V, P);

}

void Player::Render()
{
	PresentClip->Render();
}


void Player::StartJump()
{
	if (bIsPlaying) {
		PresentClip = Jump;
		if (bOnGround == true)
		{
			velocity = 50.0f;
			bOnGround = false;
			presentJump++;
		}
		else
		{
			if (presentJump < maxJump)
			{
				velocity = 3.5f;
				bOnGround = false;
				presentJump++;
			}
		}
	}
}

void Player::EndJump()
{
	if (bIsPlaying) {
		if (velocity > 0.25f)
		{
			velocity = 0.25;
			PresentClip = Walk;
		}
	}
}

void Player::SetCrouch()
{
	PresentClip = Crouch;
}


bool Player::CollisionTest(vector<Enemy*>& input)
{
	for (auto a : input)
	{
		RECT temp;
		if (IntersectRect(&temp, &(this->GetWorldLocation()), &(a->GetWorldLocation())))
		{
			deathCount++;
			bIsPlaying = false;
			PresentClip = Die;
			return true;
		}
	}
	return false;
}


