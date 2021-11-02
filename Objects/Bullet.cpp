#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	sprite = new Sprite(Textures + L"Mario/Bullets.png", shaderFile, 173, 155, 183, 167);

	position = start;
	sprite->Position(position);

	float radian = Math::ToRadian(angle);
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed;

}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position += velocity;

	sprite->Position(position);
	sprite->Update(V, P);

	CollisionTest();
	//testMethod();

}

void Bullet::Render()
{
	sprite->Render();
}

void Bullet::CollisionTest()
{
	int temp = CheckOverlapWall();

	switch (temp)
	{
	case 1:
	{
		OverlapTop();
		break;
	}
	case 2:
	{
		OverlapBottom();
		break;
	}
	case 3:
	{
		OverlapLeft();
		break;
	}
	case 4:
	{
		OverlapRight();
		break;
	}
	default:
		break;
	}
}

void Bullet::testMethod()
{
	if (IsOnTop() | IsOnBottom() | IsOnRight() | IsOnLeft())
		setStop();

}

int Bullet::CheckOverlapWall()
{
	return IsOnTop() ? 1 :
		IsOnBottom() ? 2 :
		IsOnLeft() ? 3 :
		IsOnRight() ? 4 : 0;
}

bool Bullet::IsOnTop()
{
	return position.y >= (float)Height ?
		true : false;
}

bool Bullet::IsOnBottom()
{
	return position.y <= 0.0f ?
		true : false;
}

bool Bullet::IsOnLeft()
{
	return position.x <= 0.0f ?
		true : false;
}

bool Bullet::IsOnRight()
{
	return position.x >= (float)Width ?
		true : false;
}

void Bullet::OverlapTop()
{
	D3DXVECTOR2 n(0.0f, -1.0f);
	velocity = GetReflectionVector(n);
}

void Bullet::OverlapBottom()
{
	D3DXVECTOR2 n(0.0f, 1.0f);
	velocity = GetReflectionVector(n);
}

void Bullet::OverlapLeft()
{
	D3DXVECTOR2 n(1.0f, 0.0f);
	velocity = GetReflectionVector(n);
}

void Bullet::OverlapRight()
{
	D3DXVECTOR2 n(-1.0f, 0.0f);
	velocity = GetReflectionVector(n);
}

void Bullet::setStop()
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}

D3DXVECTOR2 Bullet::GetReflectionVector(D3DXVECTOR2 v2n)
{
	return velocity + 2 * v2n *(D3DXVec2Dot(&(-velocity), &v2n));
}
