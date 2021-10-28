#include "stdafx.h"
#include "Ground.h"

Ground::~Ground()
{
}

void Ground::Move()
{
	Position(Position().x - 1.0f, Position().y);
	if (Position().x < 512)
	{
		Position(Position().x + 1024, Position().y);
	}
}

void Ground::Update()
{
	__super::Update();
	D3DXVECTOR2 position = Position();
	position.x -= MoveSpeed;
	if (position.x < baseLocation.x - 512.0f)
	{
		position.x += 512.0f;
	}
	Position(position);
}
