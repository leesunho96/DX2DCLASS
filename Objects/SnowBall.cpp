#include "stdafx.h"
#include "SnowBall.h"

SnowBall::SnowBall() : animation(new Animation()), position(D3DXVECTOR2(0.0f, 0.0f)), rotation(D3DXVECTOR3(0, 0, 0)),
scale(D3DXVECTOR2(1.0f, 1.0f)), direction(D3DXVECTOR2(0, 0))
{
	Clip* clip;

	wstring TextureFile = Textures + L"TianSouls/SnowBall.png";
	wstring ShaderFile = Shaders + L"009_Sprite.fx";

	// GoToTop
	{
		clip = new Clip();

		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 0 , 0  , 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 0 , 96 , 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 0 , 144, 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 0 , 192, 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 0 , 240, 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 0 , 288, 48 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 48, 0  , 96 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 48, 96 , 96 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 48, 144, 96 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 48, 192, 96 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 192, 48, 240, 96 ), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 240, 48, 288, 96 ), 0.1f);		
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 0  , 96, 0  , 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 48 , 96, 96 , 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 96 , 96, 144, 144), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 144, 96, 192, 144), 0.1f);
		animation->AddClip(clip);
	}
	animation->SetRotation(rotation);
	animation->SetAbsoluteScale(50.0f, 50.0f);
	
}

SnowBall::~SnowBall()
{
}

void SnowBall::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!bIsValid)
		return;

	position += direction * 200.0f * Timer->Elapsed();

	animation->SetPosition(position);
	animation->SetRotation(rotation);
	animation->Update(V, P);
	animation->Play(iPlayAnimationNum);
}

void SnowBall::Render()
{
	if (!bIsValid)
		return;
	animation->Render();
}
