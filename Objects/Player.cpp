#include "stdafx.h"
#include "Objects/Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusoffset(-400, -300)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 94, 40), 0.3f);
		animation->AddClip(clip);
	}

	//Run
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
	bool bMove = false;
	if (activate)
	{
		if (!bOnGround)
		{
			position.y += Timer->Elapsed() * gravity;
			angle = 0.0f;
			gravity += -500.0f * Timer->Elapsed();
		}
		else
		{
			if (Key->Down(VK_SPACE))
			{
				bOnGround = false;
				gravity = 500.0f;
				position.y += 10.0f;
			}
		}
		if (Key->Press('A'))
		{
			bMove = true;
			bToRIght = false;
			position.x -= moveSpeed * Timer->Elapsed() * cosf(Math::ToRadian(angle));
			position.y -= moveSpeed * Timer->Elapsed() * sinf(Math::ToRadian(angle));
			Rotation = D3DXVECTOR3(Rotation.x, 180, Rotation.z);

		}
		else if (Key->Press('D'))
		{
			bMove = true;
			bToRIght = true;
			position.x += moveSpeed * Timer->Elapsed() * cosf(Math::ToRadian(angle));
			position.y += moveSpeed * Timer->Elapsed() * sinf(Math::ToRadian(angle));
			Rotation = D3DXVECTOR3(Rotation.x, 0, Rotation.z);
		}
	}
	if (bToRIght)
		animation->SetRotationDegree(Rotation.x, 0, angle);
	else
		animation->SetRotationDegree(Rotation.x, 180, -angle);

	animation->SetPosition(position);
	animation->Play(bMove ? 1 : 0);
	animation->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	if (ImGui::Button("ActivatePlayer?"))
	{
		activate = activate == true ? false : true;
	}
	animation->Render();

}

void Player::SetDegree(float x)
{
	if (x > 90.0f)
	{
		angle = x - 180.0f;
	}
	else if (x < -90.0f)
	{
		angle = x + 180.0f;
	}
	else
		angle = x;

	bOnGround = true;
}

