#include "stdafx.h"
#include "Bullet.h"



vector<Bullet*> Bullet::bulletvector;
Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	sprite = new Sprite(
		Textures + L"PuzzleBobble/puzzlebobble.png",
		shaderFile, 
		27, 814, 
		27 + 30, 814 + 30);

	position = start;
	sprite->Position(position);
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Position(D3DXVECTOR2 & pos)
{
	this->position = pos;
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position += velocity;

	sprite->Position(position);
	sprite->Update(V, P);
	CollisionTest();
}

void Bullet::Render()
{
	sprite->Render();
}

void Bullet::setVelocity(float degree)
{
	isMoving = true;
	float radian = Math::ToRadian(degree);
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);

	velocity *= 5.0f;
}

RECT Bullet::GetWorldPosition()
{
	return sprite->GetRect();
}

bool Bullet::getIsmoving()
{
	return isMoving;
}

pair<int, int> Bullet::getArrayList()
{
	pair<int, int> temp;
	temp.first = (int)((position.x - 150) / 30);
	temp.second = (int)((600 - position.y) / 30);
	return temp;
}

D3DXVECTOR2 Bullet::getVelocity()
{
	return velocity;
}

void Bullet::isOverlap(Bullet * past, Bullet * target)
{
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
	if (isMoving)
	{
		RECT temp;

		for (size_t i = 0; i < bulletvector.size() - 1; i++)
		{
			if (IntersectRect(
				&temp,
				&(bulletvector[i]->GetWorldPosition()),
				&(bulletvector[bulletvector.size() - 1]->GetWorldPosition())
			))
			{
				setStop();
				isMoving = false;
			}

		}
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
	return position.x <= 250.0f ?
		true : false;
}

bool Bullet::IsOnRight()
{
	return position.x >= (float)Width - 250.0f ?
		true : false;
}

void Bullet::OverlapTop()
{
	velocity = D3DXVECTOR2(0, 0);
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
