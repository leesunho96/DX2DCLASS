#include "stdafx.h"
#include "Player.h"

Player::Player(wstring shaderFile) : Rect(shaderFile),
	speed(50.0f), velocity(0.0f), gravity(-1.5f), bOnGround(true)
{
}

Player::Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color) 
	: Rect(shaderFile, position, scale, color),
	speed(50.0f), velocity(0.0f), gravity(-1.5f), bOnGround(true)
{
}

Player::~Player()
{
}

void Player::Update()
{
	__super::Update(); // 상위 클래스 Update 먼저 호출.

	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta(); // Time::Delta : 컴퓨터마다 속도가 다름. 해당 속도는 달라도 간격은 동일. 해당값을 보정하기 위함. 서버 렉 통신 관련 문제 해결.

	if (bOnGround == false)
	{
		position.y += velocity;
		Position(position);
	}

	if (position.y < Scale().y * 0.5f)
	{
		position.y = Scale().y * 0.5f;
		velocity - 0.0f;

		bOnGround = true;
		Position(position);
	}
}

void Player::MoveLeft()
{
	D3DXVECTOR2 position = Position();
	position.x -= speed * Time::Delta();

	Position(position);
}

void Player::MoveRight()
{
	D3DXVECTOR2 position = Position();
	position.x +=speed * Time::Delta();

	Position(position);
}

void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.75f;
		bOnGround = false;

	}
}

void Player::EndJump()
{
	if (velocity > 0.25f)
	{
		velocity = 0.25;
	}
}
