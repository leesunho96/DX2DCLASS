#include "stdafx.h"
#include "Objects/Ball.h"

Ball::Ball(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed) 
	: startPosition(start), speed(speed), angle(angle)
{
	sprite = new Sprite(
		Textures + L"/Alkanoid/Blocks.png",
		shaderFile,
		455, 450,
		485, 480);

	InitializeVelocityPosition(start, angle, speed);

}

void Ball::InitializeVelocityPosition(const D3DXVECTOR2 &start, float angle, float speed)
{
	position = start;
	sprite->Position(position);

	float radian = Math::ToRadian(angle);
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed;
}

Ball::~Ball()
{
	SAFE_DELETE(sprite);
}

void Ball::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{	
	position += velocity;

	sprite->Position(position);
	sprite->Update(V, P);

	CollisionTest();
}

void Ball::Render()
{
	sprite->Render();
}

void Ball::CollisionTestWithBall(Sprite * others)
{

	D3DXVECTOR2 ballTextureSize = this->sprite->TextureSize();
	D3DXVECTOR2 ballPosition = this-> position;

	D3DXVECTOR2 playerTextureSize = others->TextureSize();
	D3DXVECTOR2 playerPosition = others->Position();
	float adjustvalue = 1.0f;


	//if (playerPosition.x - playerTextureSize.x * 0.5f + adjustvalue >= ballPosition.x + ballTextureSize.x * 0.5f)
	//{
	//	// 1번 위치
	//	if (playerPosition.y + playerTextureSize.y * 0.5f - adjustvalue <= ballPosition.y - ballTextureSize.y * 0.5f)
	//	{
	//		velocity = -velocity;
	//		return;
	//	}
	//	//if(playerPosition.y )
	//	
	//}

	if ((playerPosition.x - playerTextureSize.x * 0.5f + adjustvalue <= ballPosition.x + ballTextureSize.x * 0.5f) &&
		playerPosition.x + playerTextureSize.x * 0.5f - adjustvalue >= ballPosition.x - ballTextureSize.x * 0.5f)
	{
		if (playerPosition.y > ballPosition.y)
		{
			// 7번
			OverlapOthersBottom();
			return;
		}
		else
		{
			// 2번
			OverlapTop();
			return;
		}
	}
	else
	{
		if ((playerPosition.x - playerTextureSize.x * 0.5f + adjustvalue >= ballPosition.x + ballTextureSize.x * 0.5f))
		{
			OverlapRight();
			return;
		}
		else if((playerPosition.x + playerTextureSize.x * 0.5f - adjustvalue <= ballPosition.x - ballTextureSize.x * 0.5f))
		{
			OverlapLeft();
			return;
		}
		else
		{
			velocity = -velocity;
			return;
		}
	}
}

void Ball::CollisionTest()
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
		OverlapDieSection();
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

void Ball::testMethod()
{
	if (IsOnTop() | IsOnBottom() | IsOnRight() | IsOnLeft())
		setStop();

}

int Ball::CheckOverlapWall()
{
	return IsOnTop() ? 1 :
		IsOnBottom() ? 2 :
		IsOnLeft() ? 3 :
		IsOnRight() ? 4 : 0;
}

bool Ball::IsOnTop()
{
	return position.y >= (float)Height ?
		true : false;
}

bool Ball::IsOnBottom()
{
	return position.y <= 0.0f ?
		true : false;
}

bool Ball::IsOnLeft()
{
	return position.x <= 220.0f ?
		true : false;
}

bool Ball::IsOnRight()
{
	return position.x >= 580.0f ?
		true : false;
}

void Ball::OverlapTop()
{
	D3DXVECTOR2 n(0.0f, -1.0f);
	velocity = GetReflectionVector(n);
}

void Ball::OverlapDieSection()
{	
	InitializeVelocityPosition(startPosition, angle, speed);
}

void Ball::OverlapLeft()
{
	D3DXVECTOR2 n(1.0f, 0.0f);
	velocity = GetReflectionVector(n);
}

void Ball::OverlapRight()
{
	D3DXVECTOR2 n(-1.0f, 0.0f);
	velocity = GetReflectionVector(n);
}

void Ball::OverlapOthersBottom()
{
	D3DXVECTOR2 n(0.0f, 1.0f);
	velocity = GetReflectionVector(n);
}

void Ball::setStop()
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}

D3DXVECTOR2 Ball::GetReflectionVector(D3DXVECTOR2 v2n)
{
	return velocity + 2 * v2n *(D3DXVec2Dot(&(-velocity), &v2n));
}
