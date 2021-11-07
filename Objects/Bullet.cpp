#include "stdafx.h"
#include "Bullet.h"
#include "Objects/Arrow.h"

extern Bullet* MAP[10][MAXARRHEIGHT];
extern Bullet* tempBullet;

//vector<Bullet*> Bullet::bulletVector;

void Bullet::Initialize(std::wstring &shaderFile, const D3DXVECTOR2 &start)
{
	int rand = Math::Random(1, 3);
	pair<float, float> startXY;
	switch (rand)
	{
	case 1:
		startXY.first = 27;
		startXY.second = 814;
		type = 1;
		break;
	case 2:
		startXY.first = 28;
		startXY.second = 911;
		type = 2;
		break;
	case 3:
		startXY.first = 27;
		startXY.second = 1009;
		type = 0;
		break;
	}
	sprite = new Sprite(
		Textures + L"PuzzleBobble/puzzlebobble.png",
		shaderFile,
		startXY.first, startXY.second,
		startXY.first + 30, startXY.second + 30);

	position = start;
	sprite->Position(position);
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	Initialize(shaderFile, start);
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Position(D3DXVECTOR2 & pos)
{
	position = pos;
	sprite->Position(position);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (isMoving)
	{
		position += velocity;
		CollisionTest();
	}
	sprite->Position(position);
	sprite->Update(V, P);

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

	velocity *= 0.5f;
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
	temp.first = (int)((position.x - 250) / 30);
	temp.second = (int)((515 - position.y) / 30);
	return temp;
}

D3DXVECTOR2 Bullet::getVelocity()
{
	return velocity;
}

void Bullet::isOverlap(Bullet * past, Bullet * target)
{
}


void Bullet::GetAdjustBulletPair(std::pair<int, int> &temp, std::pair<int, int> &temp2)
{
	while (MAP[temp.first][temp.second] != nullptr)
	{
		if (MAP[temp.first][temp.second]->position.x + 14.0f < this->position.x)
		{
			temp2.first + 1 < 10 ? temp2.first++ : temp2.first;

		}
		else if (MAP[temp.first][temp.second]->position.x - 14.0f > this->position.x)
		{
			temp2.first - 1 >= 10 ? temp2.first-- : temp2.first;
		}
		if (MAP[temp.first][temp.second]->position.y - 14.0f > this->position.y)
		{
			temp2.second++;
		}
		temp = temp2;
	}
}

void Bullet::SetAdjustedBulletPosition(std::pair<int, int> &temp, D3DXVECTOR2 &tempPosition)
{
	MAP[temp.first][temp.second] = tempBullet;
	tempPosition = D3DXVECTOR2(250.0f + 30.0f * temp.first,
		515 - 30.0f * temp.second);
	MAP[temp.first][temp.second]->Position(tempPosition);
	tempBullet->setStop();
	tempBullet->isGetRivision = true;
}

void Bullet::AllocateBullet()
{
	pair<int, int> temp = getArrayList();
	pair<int, int> temp2 = temp;
	D3DXVECTOR2 tempPosition;
	GetAdjustBulletPair(temp, temp2);
	SetAdjustedBulletPosition(temp, tempPosition);

	int bulletNum = 1;
	
	
	
	
	
	tempBullet = nullptr;
}


void Bullet::CollisionTest()
{
	int temp = CheckOverlapWall();

	switch (temp)
	{
	case 1:
	{
		OverlapTop();
		AllocateBullet();
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

	bool isbreak = false;
	if (!isGetRivision && isMoving)
	{
		RECT temp;

		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < MAXARRHEIGHT; j++)
			{
				if (MAP[i][j] != nullptr)
				{
					if (
						IntersectRect(
							&temp,
							&MAP[i][j]->GetWorldPosition(),
							&this->GetWorldPosition())
						)
					{
						AllocateBullet();
						isbreak = true;
						break;
					}
				}
			}
			if (isbreak)
				break;
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
	return position.y >= (float)Height - 85.0f ?
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
	Key->setAccept();
	isMoving = false;
}

D3DXVECTOR2 Bullet::GetReflectionVector(D3DXVECTOR2 v2n)
{
	return velocity + 2 * v2n *(D3DXVec2Dot(&(-velocity), &v2n));
}
