#include "stdafx.h"
#include "SnowBall.h"
#include "Player.h"

SnowBall::SnowBall() : animation(new Animation()), position(D3DXVECTOR2(0.0f, 0.0f)), rotation(D3DXVECTOR3(0, 0, 0)),
scale(D3DXVECTOR2(1.0f, 1.0f)), direction(D3DXVECTOR2(-1, 0)), stopwatch(StopWatch()), bIsValid(false)
{
	InitializeAnimation();
}

void SnowBall::InitializeAnimation()
{
	Clip* clip;

	wstring TextureFile = Textures + L"TianSouls/SnowBall.png";
	wstring ShaderFile = Shaders + L"009_Sprite.fx";

	// GoToTop
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0, 0, 48, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48, 0, 96, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96, 0, 144, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 0, 192, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 0, 240, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 0, 288, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0, 48, 48, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48, 48, 96, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96, 48, 144, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 48, 192, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 48, 240, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 48, 288, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0, 96, 48, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48, 96, 96, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96, 96, 144, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 96, 192, 144), 0.1f);
		animation->AddClip(clip);
	}
	animation->SetPosition(position);
	animation->SetRotation(rotation);
	animation->SetScale(1, 1);
	animation->Play(0);
	ResetStopwatch();
}

SnowBall::SnowBall(Player * player) : player(player)
{
	InitializeAnimation();
}

SnowBall::~SnowBall()
{
}

void SnowBall::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!bIsValid)
		return;

	if (stopwatch.IsOver())
	{
		bIsValid = false;
		ResetStopwatch();
	}
	stopwatch.Update();
	position += direction * 200.0f * Timer->Elapsed();




	if (player->GetSprite()->OBB(animation->GetSprite()))
	{
		player->SetNuckBack(position);
		ResetStopwatch();
		bIsValid = false;
	}
	animation->Play(iPlayAnimationNum);
	animation->SetPosition(position);
//	animation->SetRotation(rotation);
	animation->Update(V, P);
}

void SnowBall::Render()
{
	if (!bIsValid)
		return;
	animation->Render();
}

void SnowBall::ResetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	animation->SetPosition(pos);	
	ResetStopwatch();
}

void SnowBall::ResetStopwatch()
{
	stopwatch.ResetTimer();
	stopwatch.SetTimer(3.0f);	
}
