#include "stdafx.h"
#include "Objects/Ball.h"
#include "Objects/Player.h"

extern bool istouch;
extern Player* player;
void SetIsTouch() { istouch = true; }

Ball::Ball(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
	: startPosition(start), speed(speed), angle(angle)
{
	sprite = new Sprite(
		Textures + L"/Alkanoid/Blocks.png",
		shaderFile,
		455, 450,
		485, 480);

	InitializeVelocityPosition(start, angle, speed);
	sprite->DrawBound(true);
	sprite->Scale(0.5f, 0.5f);

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
	ImGui::SliderFloat("ball Position X", &position.x, -500, 500);
	ImGui::SliderFloat("ball Position Y", &position.y, -500, 500);
}

void Ball::CollisionTestWithBall(Sprite * others)
{

	D3DXVECTOR2 ballTextureSize = this->sprite->TextureSize();
	D3DXVECTOR2 ballPosition = this->position;

	D3DXVECTOR2 playerTextureSize = others->TextureSize();
	D3DXVECTOR2 playerPosition = others->Position();
	
	float adjustvalue = 3.0f;
	// 외부 코드. 분석해보자.
	float overlapLeft{playerPosition.x + playerTextureSize.x * 0.5f - (ballPosition.x - ballTextureSize.x * 0.5f)}; //mBall.right() - mBrick.left() };
	float overlapRight{ -(playerPosition.x + playerTextureSize.x * 0.5f) + (ballPosition.x - ballTextureSize.x * 0.5f) };// mBrick.right() - mBall.left() };
	float overlapTop{ ballPosition.y - ballTextureSize.y * 0.5f - (playerPosition.y + playerTextureSize.y * 0.5f) };//mBall.bottom() - mBrick.top() };
	float overlapBottom{ -(ballPosition.y - ballTextureSize.y * 0.5f) + (playerPosition.y + playerTextureSize.y * 0.5f) };// mBrick.bottom() - mBall.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
	{
		if (ballFromLeft)
		{
			OverlapRight();
			//position.x -= adjustvalue;
		}
		else
		{
			OverlapLeft();
			//position.x += adjustvalue;
		}		
	}
	else
	{
		if (ballPosition.y > playerPosition.y)
		{
			OverlapTop();
			
		}
		else
		{
			OverlapOthersBottom();
		}
	}
	SetIsTouch();
}

void Ball::CollisionTestWithPlayer(Sprite * player)
{
	D3DXVECTOR2 ballTextureSize = this->sprite->TextureSize();
	D3DXVECTOR2 ballPosition = this->position;

	D3DXVECTOR2 playerTextureSize = player->TextureSize();
	D3DXVECTOR2 playerPosition = player->Position();


	float adjustvalue = 1.0f;


	if (playerPosition.x - playerTextureSize.x * 0.5f + adjustvalue >= ballPosition.x + ballTextureSize.x * 0.5f)
	{
		SetIsTouch();
		if (playerPosition.y - playerTextureSize.y * 0.5f + adjustvalue >= ballPosition.y + ballTextureSize.y * 0.5f)
		{
			velocity = -velocity;

			position.x -= adjustvalue;
			position.y -= adjustvalue;
			return;
		}
		else if (playerPosition.y + playerTextureSize.y * 0.5f - adjustvalue <= ballPosition.y - ballTextureSize.y * 0.5f)
		{
			velocity = -velocity;
			position.x -= adjustvalue;
			position.y += adjustvalue;
			return;
		}
		else
		{
			OverlapLeft();
			return;
		}

	}
	else if (playerPosition.x + playerTextureSize.x * 0.5f - adjustvalue <= ballPosition.x - ballTextureSize.x * 0.5f)
	{
		SetIsTouch();
		if (playerPosition.y - playerTextureSize.y * 0.5f + adjustvalue >= ballPosition.y + ballTextureSize.y * 0.5f)
		{
			velocity = -velocity;
			position.x += adjustvalue;
			position.y -= adjustvalue;
			return;
		}
		else if (playerPosition.y + playerTextureSize.y * 0.5f - adjustvalue <= ballPosition.y - ballTextureSize.y * 0.5f)
		{
			velocity = -velocity;
			position.x += adjustvalue;
			position.y += adjustvalue;
			return;
		}
		else
		{
			OverlapRight();
			return;
		}
	}
	else /*if ((playerPosition.x - playerTextureSize.x * 0.5f + adjustvalue <= ballPosition.x + ballTextureSize.x * 0.5f) &&
		playerPosition.x + playerTextureSize.x * 0.5f - adjustvalue >= ballPosition.x - ballTextureSize.x * 0.5f)*/
	{
		SetIsTouch();
		if (playerPosition.y > ballPosition.y)
		{
			// 7번
			OverlapOthersBottom();
			position.y -= 0.1f; 
			return;
		}
		else
		{
			// 2번
			OverlapTop();
			position.y += 0.1f; 
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
		OverlapOthersBottom();
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
	position.y += 1.0f;
}

void Ball::OverlapDieSection()
{
	D3DXVECTOR2 temp = player->GetSprite()->Position();
	temp.y += 50.0f;
	InitializeVelocityPosition(temp, angle, speed);
}

void Ball::OverlapLeft()
{
	D3DXVECTOR2 n(1.0f, 0.0f);
	velocity = GetReflectionVector(n);
	position.x += 1.0f;
}

void Ball::OverlapRight()
{
	D3DXVECTOR2 n(-1.0f, 0.0f);
	velocity = GetReflectionVector(n);
	position.x -= 1.0f;
}

void Ball::OverlapOthersBottom()
{
	D3DXVECTOR2 n(0.0f, 1.0f);
	velocity = GetReflectionVector(n);
	position.y -= 1.0f;
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
