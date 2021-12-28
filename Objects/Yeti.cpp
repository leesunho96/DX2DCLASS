#include "stdafx.h"
#include "Yeti.h"

Yeti::Yeti(D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	wstring TextureFile = Textures + L"TianSouls/yeti.png";
	wstring ShaderFile = Shaders + L"009_Sprite.fx";

	animation = new Animation();
	Clip* clip;

	// Idle
	{
		//clip->AddFrame(new Sprite)
	}
	// Throw Snow Ball To Up
	{

	}
	// Throw Snow Ball To RightUp
	{

	}
	// Throw Snow Ball To Right
	{

	}
	// Throw Snow Ball To RightDown
	{

	}
	// Throw Snow Ball To Down
	{

	}

	// Roll To Up
	{

	}
	// Roll To RightUp
	{

	}
	// Roll To Right
	{

	}
	// Roll To RightDown
	{

	}
	// Roll To Down
	{

	}

	// Die While See Up
	{

	}
	// Die While See RightUp
	{

	}
	// Die While See Right
	{

	}
	// Die While See RightDown
	{

	}
	// Die While See Down
	{

	}

}

Yeti::~Yeti()
{
}

void Yeti::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	animation->Update(V, P);
	animation->SetPosition(position);
	animation->SetRotation(rotation);
	animation->Play(iPlayAnimationNum);
}

void Yeti::Render()
{
	animation->Render();
}

void Yeti::ApplyDamage(Sprite * sprite)
{
}

