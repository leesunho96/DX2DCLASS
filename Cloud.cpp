#include "stdafx.h"
#include "Cloud.h"

void Cloud::setPosition(D3DXVECTOR2 & position)
{
	Position(position);
}

void Cloud::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	__super::Update(V, P);
	if (!isStop)
	{
		D3DXVECTOR2 position = Position();
		position.x -= speed;
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
			speed = Math::Random(0.01f, 0.2f);
			coolTime = respawnTime;
		}
	}
}

