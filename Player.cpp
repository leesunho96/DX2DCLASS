#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"

Player::Player(wstring shaderFile, wstring imgFile) : Rect(shaderFile, imgFile),
speed(50.0f), velocity(0.0f), gravity(-0.7f), bOnGround(true)
{
}

Player::Player(wstring shaderFile, wstring imgFile, D3DXVECTOR2 position, D3DXVECTOR2 scale)
	: Rect(shaderFile,imgFile, position, scale),
	speed(50.0f), velocity(0.0f), gravity(-0.7f), bOnGround(true)
{
}

Player::~Player()
{
}

void Player::Update()
{
	__super::Update(); // ���� Ŭ���� Update ���� ȣ��.

	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta(); // Time::Delta : ��ǻ�͸��� �ӵ��� �ٸ�. �ش� �ӵ��� �޶� ������ ����. �ش簪�� �����ϱ� ����. ���� �� ��� ���� ���� �ذ�.

	if (bOnGround == false)
	{
		position.y += velocity;
		Position(position);
	}

	if (position.y < Scale().y * 0.5f)
	{
		position.y = Scale().y * 0.5f;
		velocity = 0.0f;
		bOnGround = true;
		presentJump = 0;
		Position(position);
	}
}


void Player::StartJump()
{
	if (bOnGround == true)
	{		
		velocity = 3.5f;
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

void Player::EndJump()
{
	if (velocity > 0.25f)
	{
		velocity = 0.25;	
	}


}

void Player::CollisionTest(vector<Enemy*>& input)
{
	//for (int i = 0; i < input.size(), i++;)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp,
	//		&(input[i]->GetWorldLocation()),
	//		&(this->GetWorldLocation()
	//			)))
	//	{
	//		deathCount++;
	//	}
	//}
	for (auto a : input)
	{
		RECT temp;
		if (IntersectRect(&temp, &(this->GetWorldLocation()), &(a->GetWorldLocation())))
		{
			deathCount++;
			a->Overlap();
		}
	}
}


