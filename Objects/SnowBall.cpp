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

//https://kr.123rf.com/photo_85187738_%EB%8F%85%EC%84%B1-%ED%8F%AD%EB%B0%9C-%ED%8A%B9%EC%88%98-%ED%9A%A8%EA%B3%BC-fx-%EC%95%A0%EB%8B%88%EB%A9%94%EC%9D%B4%EC%85%98-%ED%94%84%EB%A0%88%EC%9E%84-%EC%8A%A4%ED%94%84%EB%9D%BC%EC%9D%B4%ED%8A%B8-%EC%8B%9C%ED%8A%B8-%EA%B2%8C%EC%9E%84-%EB%B9%84%EB%94%94%EC%98%A4-%EB%B0%8F-%EB%A7%8C%ED%99%94%EC%97%90%EC%84%9C-%ED%94%8C%EB%9E%98%EC%8B%9C-%EC%95%A0%EB%8B%88%EB%A9%94%EC%9D%B4%EC%85%98%EC%9D%84%EC%9C%84%ED%95%9C-%EB%85%B9%EC%83%89-%EC%82%B0%EC%84%B1-%EB%8F%85%EC%84%B1-%ED%8C%8C%EC%9B%8C-%ED%8F%AD%EB%B0%9C-%ED%94%84%EB%A0%88%EC%9E%84-.html
	// GoToTop
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 0 , 48, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 0 , 96, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 0 , 144, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 0 , 192, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 0 , 240, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 0 , 288, 48), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 48, 48, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 48, 96, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 48, 144, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 48, 192, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 48, 240, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 48, 288, 96), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 96, 48, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 96, 96, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 96, 144, 144), 0.1f);
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
	SAFE_DELETE(animation);
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
	position += direction * 400.0f * Timer->Elapsed();




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
	ImGui::LabelText("SnowBallPosition :", "%.0f, %.0f", position.x, position.y);
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
