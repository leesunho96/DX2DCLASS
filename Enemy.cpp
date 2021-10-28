#include "stdafx.h"
#include "Enemy.h"

void Enemy::setPosition(D3DXVECTOR2 & position)
{
	Position(position);
}

void Enemy::Update()
{
	__super::Update();
	if (!isStop)
	{
		D3DXVECTOR2 position = Position();
		position.x -= MoveSpeed;
		if (position.x < 0.0f)
		{
			position.x = 1300.0f;
			isStop = true;

		}
		Position(position);
	}
	else
	{
		coolTime--;
		if (coolTime == 0)
		{
			isStop = false;
			respawnTime = Math::Random(5000, 10000);
			coolTime = respawnTime;
		}
	}
}

void Enemy::Overlap()
{
	isStop = true;
	Position(1300.0f, Position().y);
}
