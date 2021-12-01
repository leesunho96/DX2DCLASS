#include "stdafx.h"
#include "Bricks.h"
#include "Renders/Animation.h"
#include "Objects/Ball.h"
#include "Objects/Item.h"

extern ItemMemoryPool* itempool;
extern Ball* ball;

Bricks::Bricks(int type, D3DXVECTOR2 position) : IBRICKSINTERFACE(), Position(position)
{
	animation = new Animation;
	Clip* clip;
	wstring TexturesName = Textures + L"/Alkanoid/Blocks.png";
	wstring ShaderName = Shaders + L"009_Sprite.fx";

	D3DXVECTOR2 startPosition(324, 0);
	D3DXVECTOR2 endPosition(378, 22);


	switch (type)
	{
	case 0:
		// IDLE
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 324, 0, 378, 22), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 1
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 44.0f, 
											endPosition.x, endPosition.y + 44.0f), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 2
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 88.0f,
				endPosition.x, endPosition.y + 88.0f), 1.0f);
			animation->AddClip(clip);
		}
		// 부서지는 애니메이션
		{
			clip = new Clip();
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 254.0f, 139.0f,
				318.0f, 167.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 254.0f, 171.0f,
				318.0f, 199.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 254.0f, 202.0f,
				318.0f, 232.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 254.0f, 234.0f,
				318.0f, 265.0f), animationTime);
			animation->AddClip(clip);
		}
		break;
	case 1:
		// IDLE
		{
			startPosition.x += 54.0f;
			endPosition.x += 54.0f;
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, 0, endPosition.x, 22), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 1
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 44.0f,
				endPosition.x, endPosition.y + 44.0f), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 2
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 88.0f,
				endPosition.x, endPosition.y + 88.0f), 1.0f);
			animation->AddClip(clip);
		}
		// 부서지는 애니메이션
		{
			clip = new Clip();
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 319.0f, 139.0f,
				382.0f, 167.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 319.0f, 171.0f,
				382.0f, 199.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 319.0f, 202.0f,
				382.0f, 232.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 319.0f, 234.0f,
				382.0f, 265.0f), animationTime);
			animation->AddClip(clip);
		}
		break;
	case 2:
		// IDLE
		{
			startPosition.x += 108.0f;
			endPosition.x += 108.0f;
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, 0, endPosition.x, 22), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 1
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 44.0f,
				endPosition.x, endPosition.y + 44.0f), 1.0f);
			animation->AddClip(clip);
		}
		// BREAKING 2
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, startPosition.x, startPosition.y + 88.0f,
				endPosition.x, endPosition.y + 88.0f), 1.0f);
			animation->AddClip(clip);
		}
		// 부서지는 애니메이션
		{
			clip = new Clip();
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 383.0f, 139.0f,
				445.0f, 167.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 383.0f, 171.0f,
				445.0f, 199.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 383.0f, 202.0f,
				445.0f, 232.0f), animationTime);
			clip->AddFrame(new Sprite(TexturesName, ShaderName, 383.0f, 234.0f,
				445.0f, 265.0f), animationTime);
			animation->AddClip(clip);
		}
		break;		
	}

	animation->SetPosition(position);
	// 54 * 22 px
	animation->SetScale(D3DXVECTOR2(0.8, 0.8));
	animation->Play(0);

	animation->DrawBound(true);
}

Bricks::~Bricks()
{
}

void Bricks::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isAvailable)
	{
		return;
	}
	if (isPlayingBreaking)
	{
		waitingTime += Timer->Elapsed();
		if (waitingTime >= animationTime * maximumLife)
		{
			isAvailable = false;
			if (bIsHavingItem)
			{
				Item* temp = itempool->GetItemFromPool();
				temp->SetPosition(animation->GetPosition());
			}

		}

	}
	else
	{
		D3DXVECTOR2 position = animation->GetPosition();
		D3DXVECTOR2 ballPosition = ball->GetPosition();

		if ((ballPosition.y <= position.y + 30.0f && ballPosition.y >= position.y - 30.0f) && ballPosition.x <= position.x + 30.0f && ballPosition.x >= position.x -30.0f)
		{
			if (Sprite::AABB(this->animation->GetSprite(), ball->GetSprite()))
			{
				//ball->CollisionTestWithBall(animation->GetSprite());
				ball->CollisionTestWithPlayer(animation->GetSprite());
				life++;
				if (life >= maximumLife)
				{
					isPlayingBreaking = true;					
				}
			}
		}
	}
	animation->Play(life);
	animation->Update(V, P);
}

void Bricks::Render()
{
	if (!isAvailable)
		return;

	animation->Render();
}

void Bricks::SetItem()
{
	bIsHavingItem = true;
}

void Bricks::ApplyDamege()
{
	life++;
	if (life >= maximumLife)
	{
		isPlayingBreaking = true;
	}
}


