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
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9, 254, 51, 326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73, 254, 115, 326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 254, 179, 326), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 254, 241, 326), 0.3f);
		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9, 2, 51, 82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73, 2, 115, 82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 2, 179, 82), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 2, 241, 82), 0.3f);
		animation->AddClip(clip);
	}
	// Jump
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 9, 87, 51, 156), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73, 87, 115, 156), 0.3f);
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
	int setClip;

	if (isPlayingGame)
	{
		position = animation->GetPosition();
		bool bMove = false;
		D3DXVECTOR2 tempPos = position;
		RECT temp;

		RECT PlayerLocation;
		{
			PlayerLocation.left = tempPos.x - animation->TextureSize().x * 0.5f;
			PlayerLocation.top = tempPos.y - animation->TextureSize().y * 0.5f;
			PlayerLocation.right = tempPos.x + animation->TextureSize().x * 0.5f;
			PlayerLocation.bottom = tempPos.y + animation->TextureSize().y * 0.5f;
		}

		bool isoverlap = false;
		bool bisXadjustRequire = false;

		for (int i = 0; i < bg->GetObjects().size(); i++)
		{
			RECT objectRect = bg->GetObjects()[i]->GetWorldLocation();
			if (IntersectRect(&temp, &objectRect, &PlayerLocation))
			{
				if (PlayerLocation.top <= objectRect.bottom && PlayerLocation.top >= objectRect.bottom - 10.0f)
				{

					bOnGround = true;
					bIsJumpable = true;
					isoverlap = true;
					velocity = 0.0f;
				}
				else if (PlayerLocation.bottom >= objectRect.top && PlayerLocation.bottom <= objectRect.bottom + 10.0f)
				{
					velocity = -velocity;
					break;
				}

				//position.y = objectRect.bottom + bg->GetObjects()[i]->TextureSize().y * 0.5f;

				if (bg->GetObjects()[i]->GetBottom())
				{
					bisXadjustRequire = true;
				}
			}


		}


		// object Right : 1, left = 0

		//player Right : -1, left = 0
		for (size_t i = 0; i < bg->GetPipes().size(); i++)
		{
			RECT objectRect = bg->GetPipes()[i]->GetWorldLocation();

			if (IntersectRect(&temp, &objectRect, &PlayerLocation))
			{
				if ((objectRect.right + objectRect.left) *0.5f > (PlayerLocation.left + PlayerLocation.right) *0.5f && bisXadjustRequire) // 왼쪽으로 겹쳤는가?
				{
					//bOverlapLeft = false;
					this->position.x = objectRect.left - animation->TextureSize().x * 0.5f;
				}
				else if ((objectRect.right + objectRect.left) *0.5f < (PlayerLocation.left + PlayerLocation.right) *0.5f && bisXadjustRequire) // 왼쪽으로 겹쳤는가?
				{
					//bOverlapRight = true;
					this->position.x = objectRect.right + animation->TextureSize().x * 0.5f;
				}

				break;
			}
		}

		if (!isoverlap)
		{
			bOnGround = false;
		}



		velocity += gravity /** Timer->Elapsed()*/;

		// 키 입력 받은 후, 그에 따른 position 좌표 처리, 움직이는지 아닌지 bMove 변수 처리.
		KeyInput(position, bMove);

		if (!bOnGround)
		{
			position.y += velocity;
		}
		// 현재 충돌용 RECT



		if (bMove)
		{
			if (bOnGround)
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
			if (bOnGround)
			{
				setClip = 0;
			}
			else
			{
				setClip = 2;
			}
		}

		if (position.y < -1000)
		{
			position.x = -4000.0f;
			position.y = 500.0f;
			LoseLife();
		}
	}
	else
	{
		position.x = 3650.0f;
		setClip = 1;
		position.y -= 0.05f;

		if (position.y <= 200.0f)
		{
			isPlayingGame = true;
		}
	}


	animation->SetPosition(position);
	animation->Play(setClip);
	animation->Update(V, P);
	
}
void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	ImGui::SliderFloat("Character's X Pos", &position.x, -4000, 4000);
	ImGui::SliderFloat("Character's Y Pos", &position.y, -4000, 4000);
	ImGui::LabelText("LIVES", "%d", lives);
	animation->Render();

}

void Player::StartJump()
{
	if (bIsJumpable)
	{
		position.y += 1.0f;
		bOnGround = false;
		bIsJumpable = false;
		velocity = 0.65f;
	}
}

void Player::GetMushroom()
{
	if (animation->GetScale() == D3DXVECTOR2(1.0f, 1.0f))
	{
		animation->SetScale(D3DXVECTOR2(1.3f, 1.3f));
	}
}

void Player::ApplyDamege()
{
	if (animation->GetScale().x > 1.0f)
	{
		animation->SetScale(1.0f, 1.0f);
	}
	else
	{
		LoseLife();
	}
}

void Player::KeyInput(D3DXVECTOR2& position, bool& bMove)
{
	D3DXVECTOR2 tempPosition = position;
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
	if (Key->Press('D'))
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

void Player::CheckPosition(D3DXVECTOR2 & position)
{

}

void Player::EndJump()
{
	bOnGround = true;
	bIsJumpable = true;
	velocity = 0.0f;

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
