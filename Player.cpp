#include "stdafx.h"
#include "Player.h"
#define JUMPLENGTH 3.0f
Player::Player(wstring shaderFile) : Rect(shaderFile),
	speed(50.0f), velocity(0.0f), gravity(-1.0f), bOnGround(true)
{
}

Player::Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color) 
	: Rect(shaderFile, position, scale, color),
	speed(50.0f), velocity(0.0f), gravity(-1.0f), bOnGround(true)
{
}

Player::~Player()
{
}

void Player::Update()
{
	__super::Update(); // 상위 클래스 Update 먼저 호출.

	if (isAutoMove)
	{
		if(isToRight)
		{
			MoveRight();
			if (isTouchRightWall())
			{
				isToRight = false;
			}
		}
		else
		{
			MoveLeft();
			if (isTouchLeftWall())
			{
				isToRight = true;
			}
		}
	}


	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta(); // Time::Delta : 컴퓨터마다 속도가 다름. 해당 속도는 달라도 간격은 동일. 해당값을 보정하기 위함. 서버 렉 통신 관련 문제 해결.

	if (bOnGround == false)
	{
		position.y += velocity;
		Position(position);
		if (isSecondJump)
		{
			if (Position().y > secondJumpStartY)
			{
				Color(D3DXCOLOR(1, 0, 0, 1));

			}
			else
			{
				Color(D3DXCOLOR(0, 1, 0, 1));
			}
		}
		else
		{
			Color(D3DXCOLOR(0, 1, 0, 1));
		}
	}

	if (position.y < Scale().y * 0.5f)
	{
		position.y = Scale().y * 0.5f;
		velocity = 0.0f;

		bOnGround = true;
		isSecondJump = false;
		Position(position);
		Color(D3DXCOLOR(1, 1, 1, 1));
	}
}

void Player::MoveLeft()
{
	D3DXVECTOR2 position = Position();
	position.x -= speed * Time::Delta();

	if (isTouchLeftWall())
	{
		position.x = Scale().x * 0.5f;
	}
	Position(position);
}

void Player::MoveRight()
{
	D3DXVECTOR2 position = Position();
	position.x +=speed * Time::Delta();


	if (isTouchRightWall())
	{
		position.x = 1024 - Scale().x * 0.5f;
	}
	Position(position);
}

void Player::AutoMoveStart()
{
	isAutoMove = isAutoMove == true ? false : true;
}


void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity = JUMPLENGTH;
		bOnGround = false;
		
	}
	else if (isSecondJump == false)
	{
		velocity += JUMPLENGTH;
		isSecondJump = true;
		secondJumpStartY = Position().y;

	}
}

void Player::EndJump()
{
	if (velocity > 0.25f)
	{
		velocity = 0.25;
	}
}

bool Player::isTouchRightWall()
{
	return Position().x >= 1024 - Scale().x * 0.5f ? true : false;
	
}

bool Player::isTouchLeftWall()
{
	return Position().x <= Scale().x * 0.5f ? true : false;
}
