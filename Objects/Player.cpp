#include "stdafx.h"
#include "Objects/Player.h"


extern RECT rect;

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;

	//Idle 0
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 94, 40), 0.3f);
		animation->AddClip(clip);
	}

	//Run 1
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 600, 64, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 65, 600, 96, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 600, 124, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 125, 600, 154, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 158, 600, 188, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 191, 600, 222, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 224, 599, 258, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 259, 600, 294, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 295, 600, 326, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 329, 600, 360, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 362, 600, 393, 640), 0.1f);
		animation->AddClip(clip);
	}


	// Jump 2
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 190, 32, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 32, 190, 62, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 62, 190, 93, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 93, 190, 123, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 123, 190, 153, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 156, 190, 186, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 186, 190, 216, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 216, 190, 247, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 249, 190, 279, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 281, 190, 308, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 308, 190, 337, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 337, 190, 366, 237), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 366, 190, 397, 237), 0.1f);

		animation->AddClip(clip);
	}


	animation->SetPosition(position);
	animation->SetScale(scale);
	animation->Play(0);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->GetPosition();

	bool bMove = false;
	RECT temp;
	velocity += gravity;

	if (isOverlapBox())
	{
		if (isOverBox(position.y))
		{
			position.y = rect.bottom;
			bOnGround = true;
			bOnSecondFloor = true;
			bIsJumpable = true;
			velocity = 0.0f;
		}
		else if (isUnderBox(position.y))
		{
			bOnGround = false;
			bOnSecondFloor = false;
			bIsJumpable = false;
			velocity = -velocity;
		}
	}
	else
	{
		if (bOnSecondFloor)
		{
			bOnSecondFloor = false;
			bIsJumpable = false;
			bOnGround = false;
			velocity = -0.1f;
		}
	}

	if (Key->Press('A'))
	{
		bMove = true;
		position.x -= moveSpeed * Timer->Elapsed();
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (Key->Press('D'))
	{
		bMove = true;
		position.x += moveSpeed * Timer->Elapsed();
		animation->SetRotationDegree(0, 0, 0);
	}

	if (Key->Press(VK_SPACE))
	{
		StartJump();
	}



	if ((position.y < animation->TextureSize().y / 2 + 20) && !bOnGround)
	{
		position.y = animation->TextureSize().y / 2 + 20;
		velocity = 0.0f;
		bOnGround = true;
		bOnSecondFloor = false;
		bIsJumpable = true;
	}
	if (!bOnGround)
	{
		position.y += velocity;
	}
	animation->SetPosition(position);

	int setClip;

	if (bMove)
	{
		if (bOnGround || bOnSecondFloor)
		{
			setClip = 1;
		}
		else
		{
			setClip = 2;
		}
	}
	else
	{
		if (bOnGround || bOnSecondFloor)
		{
			setClip = 0;
		}
		else
		{
			setClip = 2;
		}
	}

	animation->Play(setClip);
	animation->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	animation->Render();

}

void Player::StartJump()
{
	if (bIsJumpable)
	{
		bOnGround = false;
		bOnSecondFloor = false;
		velocity = 0.8f;
	}
}

bool Player::isOverlapBox()
{
	RECT temp;
	return IntersectRect(&temp, &rect, &animation->GetWorldLocation());
}

bool Player::isOverBox(float fPositonY)
{
	return fPositonY >= rect.bottom ? true : false;
}

bool Player::isUnderBox(float fPositionY)
{
	return fPositionY < rect.bottom ? true : false;
}
