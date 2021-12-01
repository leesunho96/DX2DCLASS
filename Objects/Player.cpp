#include "stdafx.h"
#include "Objects/Player.h"
#include "Objects/Ball.h"
//#include "Systems/MemoryPool.h"
#include "Objects/Bullet.h"

extern Ball* ball;
extern BulletMemoryPool* bulletpool;
//extern MemoryPool<Bullet>* bulletPool;

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(300.0f), focusoffset(0, -120)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"/Alkanoid/Blocks.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 302, 58, 331), 0.3f);

		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip();
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 302, 58, 331), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 58, 302, 148, 331), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 148, 302, 276, 331), 99999999.0f);
		animation->AddClip(clip);
	}

	animation->SetPosition(position);
	animation->SetScale(scale);
	animation->Play(0);

	animation->DrawBound(true);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->GetPosition() - focusoffset;
	(*size) = D3DXVECTOR2(1, 1);
	
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->GetPosition();
	D3DXVECTOR2 ballPosition = ball->GetPosition();
	bulletCooltime += Timer->Elapsed();
	//if (bIsGetBulletItem)
	{
		if (Key->Press(VK_SPACE) && bulletCooltime >= 0.5f)
		{
			Bullet* temp1 = bulletpool->GetItemFromPool();
			Bullet* temp2 = bulletpool->GetItemFromPool();
			temp1->SetPosition(D3DXVECTOR2(position.x - animation->TextureSize().x * 0.5f, position.y));
			temp2->SetPosition(D3DXVECTOR2(position.x + animation->TextureSize().x * 0.5f, position.y));
			bulletCooltime = 0.0f;
		}
	}

	if (bIsGetLargerItem)
	{
		clipNum = 1;
	}
	if (bIsGetMoreBall)
	{

	}

	if (ballPosition.y <= position.y + 50.0f)
	{
		if (Sprite::AABB(this->animation->GetSprite(), ball->GetSprite()))
		{
			ball->CollisionTestWithBall(animation->GetSprite());
		}
	}
	bool bMove = false;

	if (Key->Press('A'))
	{
		bMove = true;
		if (!(position.x <= 230.0f))
		{
			position.x -= moveSpeed * Timer->Elapsed();
		}
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (Key->Press('D'))
	{
		bMove = true;
		if (!(position.x >= 570.0f))
		{
			position.x += moveSpeed * Timer->Elapsed();
		}
		
		animation->SetRotationDegree(0, 0, 0);
	}
	animation->SetPosition(position);
	animation->Play(clipNum);
	animation->Update(V, P);

}

void Player::Render()
{
	
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	
	animation->Render();

}

void Player::GetItem(int type)
{
	switch (type)
	{
	case 0:
		GetBullet();
		break;
	case 1:
		GetLargerItem();
		break;
	case 2:
		GetMoreBallItem();
		break;
	}
}
