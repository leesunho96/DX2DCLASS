#include "stdafx.h"
#include "Icycle.h"
#include "Characters/Player.h"
#include "Physics/CollisionDesc.h"
#include "Physics/CollisionSystem.h"

extern CollisionSystem* collisionsystem;

Icycle::Icycle(int type, Player* player) : stopwatch(StopWatch()), player(player), gravity(Gravity())
{
	animation = new Animation();

	Clip* clip;
	wstring TextureFile = Textures + L"TianSouls/yeti.png";
	wstring ShaderFile = Shaders + L"009_Sprite.fx";

	switch (type)
	{
			// Waiting
		case 0:
		{ 
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
				animation->AddClip(clip);
			}

			// Falling
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
				animation->AddClip(clip);
			}
			// OnGround
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 260, 963, 284, 981), 1.0f);
				animation->AddClip(clip);
			}
			break;
		}
		case 1:
		{
			// Waiting
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 135, 960, 153, 990), 1.0f);
				animation->AddClip(clip);
			}

			// Falling
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 135, 960, 153, 990), 1.0f);
				animation->AddClip(clip);
			}
			// OnGround
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 295, 963, 313, 981), 1.0f);
				animation->AddClip(clip);
			}
			break;
		}
		case 2:
		{
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 167, 960, 183, 990), 1.0f);
				animation->AddClip(clip);
			}

			// Falling
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 167, 960, 183, 990), 1.0f);
				animation->AddClip(clip);
			}
			// OnGround
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 328, 964, 344, 980), 1.0f);
				animation->AddClip(clip);
			}
			break;
		}
		case 3:
		{
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 195, 960, 220, 990), 1.0f);
				animation->AddClip(clip);
			}

			// Falling
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 195, 960, 220, 990), 1.0f);
				animation->AddClip(clip);
			}
			// OnGround
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 355, 962, 380, 981), 1.0f);
				animation->AddClip(clip);
			}
			break;
		}
	}
	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(TextureFile, ShaderFile, 230, 969, 250, 983), 1.0f);
	animation->AddClip(clip);
	
	animation->SetPosition(0, 0);
	animation->SetRotation(0, 0, 0);
	animation->SetScale(1, 1);
	ResetStopWatch(0.3f);
}

Icycle::~Icycle()
{
	SAFE_DELETE(animation);
}

void Icycle::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (StateInfo == Invalidate)
		return;

	stopwatch.Update();	
	gravity.Update();

	if (StateInfo == ValidateAndWaitFalling)
	{
		ActWhileWaitFalling();		
	}
	else if (StateInfo == ValidateAndFalling)
	{
		ActWhileFalling();
	}
	else if (StateInfo == ValidateAndFall)
	{
		gravity.SetInvalid();
		ActWhileFall();
	}
	else if (StateInfo == ValidateAndHole)
	{
		ActWhileHole();
	}
	
	animation->Play(iPlayAnimationNum);
	animation->SetPosition(position);
	animation->Update(V, P);
}

void Icycle::ActWhileHole()
{
	if (stopwatch.IsOver())
	{
		StateInfo = Invalidate;
		ResetStopWatch(0.3f);
	}
	SetCollisionDesc();
	iPlayAnimationNum = 3;
}

void Icycle::ActWhileFall()
{
	if (stopwatch.IsOver())
	{
		StateInfo = ValidateAndHole;
		ResetStopWatch(0.3f);
	}

	SetCollisionDesc();
	iPlayAnimationNum = 2;
}

void Icycle::SetCollisionDesc()
{
	CollisionDesc collisiondesc;
	collisiondesc.InitializeCollisionDesc(animation, false, false, 0);
	collisionsystem->SetCollisionDesc(collisiondesc);
}

void Icycle::ActWhileFalling()
{
	if (!gravity.GetIsValid())
	{
		gravity.SetValid();
		gravity.SetGravity(D3DXVECTOR2(0.0f, -0.0f));
		gravity.SetVelocity(D3DXVECTOR2(0.0f, -200.0f));
	}

	gravity.SetVelocity(D3DXVECTOR2(0.0f, -400.0f));
	position = gravity.GetAdjustPosition(position);

	// 플레이어와 고드름이 충돌하면 그에 따른 판정 필요.
	// 플레이어의 위치가 고드름보다 아래여야 충돌 판정.
	if (player->GetSprite()[0]->OBB(animation->GetSprite()))
	{
		if (player->GetSprite()[0]->Position().y < position.y)
		{
			player->ApplyDamege(animation->GetSprite());
		}
	}
	if (stopwatch.IsOver())
	{
		StateInfo = ValidateAndFall;
		ResetStopWatch(0.3f);
	}
	iPlayAnimationNum = 1;
}

void Icycle::ActWhileWaitFalling()
{
	if (stopwatch.IsOver())
	{
		StateInfo = ValidateAndFalling;
		ResetStopWatch(0.6f);
	}
	iPlayAnimationNum = 0;
}

void Icycle::Render()
{
	if (StateInfo == Invalidate)
		return;
	
	float temp = gravity.GetVelocity();
	ImGui::BulletText("Velocity : %f", &temp);	
	animation->Render();
}

void Icycle::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	animation->SetPosition(position);
}

void Icycle::SetInvalidate()
{
	StateInfo = Invalidate;	
}

void Icycle::SetValidate()
{
	if (StateInfo == Invalidate)
	{
		StateInfo = ValidateAndWaitFalling;
		ResetStopWatch(1.2f);
	}
}
