#include "stdafx.h"
#include "Freedom.h"

Freedom::Freedom(float speed)
{
}

Freedom::~Freedom()
{
}

void Freedom::Update()
{
	if (Key->Press(VK_LEFT))
	{
		Move(D3DXVECTOR2(-1.0f, 0.0f) * speed);
	}
	else if (Key->Press(VK_RIGHT))
	{
		Move(D3DXVECTOR2(1.0f, 0.0f) * speed);
	}

	if (Key->Press(VK_UP))
	{
		Move(D3DXVECTOR2(0, 1) * speed);

	}
	else if (Key->Press(VK_DOWN))
	{
		Move(D3DXVECTOR2(0, -1) * speed);
	}

	__super::Update();
		
}


void Freedom::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Freedom::SetPosition(D3DXVECTOR2 & vec)
{
	
}

void Freedom::Move(D3DXVECTOR2 & translation)
{
	position += translation * Timer->Elapsed();
}
