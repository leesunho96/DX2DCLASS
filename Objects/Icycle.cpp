#include "stdafx.h"
#include "Icycle.h"

Icycle::Icycle(int type) : stopwatch(StopWatch())
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
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
			}

			// Falling
			{
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
			}
			// OnGround
			{
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 260, 963, 284, 981), 1.0f);
			}
			break;
		}
		case 1:
		{
			// Waiting
			{
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 135, 960, 153, 990), 1.0f);
			}

			// Falling
			{
				clip = new Clip();
			}
			// OnGround
			{
				clip = new Clip();
			}
			break;
		}
		case 2:
		{
			{
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
			}

			// Falling
			{
				clip = new Clip();
			}
			// OnGround
			{
				clip = new Clip();
			}
			break;
		}
		case 3:
		{
			{
				clip = new Clip();
				clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 960, 124, 990), 1.0f);
			}

			// Falling
			{
				clip = new Clip();
			}
			// OnGround
			{
				clip = new Clip();
			}
			break;
		}
	}
}

Icycle::~Icycle()
{
	SAFE_DELETE(animation);
}

void Icycle::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!bIsValidate)
		return;




	animation->Play(iPlayAnimationNum);
	animation->SetPosition(position);
	animation->Update(V, P);
}

void Icycle::Render()
{
	if (!bIsValidate)
		return;
	animation->Render();
}

void Icycle::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	animation->SetPosition(position);
}

void Icycle::SetInvalidate()
{
	bIsValidate = false;
}

void Icycle::SetValidate()
{
	bIsValidate = true;
}
