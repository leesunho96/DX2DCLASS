#include "stdafx.h"
#include "Objects/Player.h"
#include "Objects/Background.h"

extern Background* bg;

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusoffset(0, -215)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"/Mario/All.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9,   254, 51,  326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73,  254, 115, 326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 254, 179, 326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 254, 241, 326), 0.3f);
		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9,   2, 51,  82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73,  2, 115, 82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 2, 179, 82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 2, 241, 82), 0.3f);
		animation->AddClip(clip);
	}
	// Jump
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9,   87, 51,  156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73,  87, 115, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 87, 179, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 87, 241, 156), 0.3f);
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

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->GetPosition() - focusoffset;
	(*size) = D3DXVECTOR2(1, 1);
	
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position = animation->GetPosition();
	bool bMove = false;

	velocity += gravity;
	// 키 입력 받은 후, 그에 따른 position 좌표 처리, 움직이는지 아닌지 bMove 변수 처리.
	KeyInput(position, bMove);


	// animation texturesize = 42, 72

	if ((position.y < animation->TextureSize().y / 2 + 50) && !bOnGround)
	{
		position.y = animation->TextureSize().y / 2 + 50;
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
	ImGui::SliderFloat("Character's X Pos", &position.x, -4000, 4000);
	animation->Render();

}

void Player::StartJump()
{
	if (bIsJumpable)
	{
		bOnGround = false;
		bOnSecondFloor = false;
		velocity = 0.1f;
	}
}

void Player::KeyInput(D3DXVECTOR2& position, bool& bMove)
{
	if (Key->Press('A'))
	{
		bMove = true;
		position.x -= moveSpeed * Timer->Elapsed();
		if (position.x < -4200.0f + animation->TextureSize().x / 2)
		{
			position.x = -4200.0f + animation->TextureSize().x / 2;
		}
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (Key->Press('D'))
	{
		bMove = true;
		position.x += moveSpeed * Timer->Elapsed();
		if (position.x > +4200.0f - animation->TextureSize().x / 2)
		{
			position.x = +4200.0f - animation->TextureSize().x / 2;
		}
		animation->SetRotationDegree(0, 0, 0);
	}

	if (Key->Press(VK_SPACE))
	{
		StartJump();
	}
}

//bool Player::isOverlapBox()
//{
//
//}

//bool Player::isOverBox(float fPositonY)
//{
//	return fPositonY >= rect.bottom ? true : false;
//}
//
//bool Player::isUnderBox(float fPositionY)
//{
//	return fPositionY < rect.bottom ? true : false;
//}
