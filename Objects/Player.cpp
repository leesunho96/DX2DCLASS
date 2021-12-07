#include "stdafx.h"
#include "Objects/Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusoffset(0, -120)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"TianSouls/player.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle : 0
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);		
		animation->AddClip(clip);
	}

	// WALK
	{
		//Walk to UP : 1 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 17, 13, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 17, 29, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 17, 45, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 51, 17, 61, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 67, 17, 77, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 82, 17, 93, 31), 0.1f);
			animation->AddClip(clip);
		}
		//Walk to Right_UP : 2 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 96, 13, 112), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 20, 96, 28, 110), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 96, 45, 112), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 96, 61, 112), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 68, 96, 77, 112), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 83, 96, 93, 112), 0.1f);
			animation->AddClip(clip);
		}
		//Walk to Right : 3 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 0, 12, 15), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 19, 0, 28, 15), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 0, 43, 15), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 51, 1, 60, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 67, 0, 76, 15), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 83, 0, 92, 15), 0.1f);
			animation->AddClip(clip);
		}
		//Walk to Right_Down : 4 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 80, 12, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 19, 80, 29, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 80, 45, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 80, 61, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 68, 80, 77, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 83, 80, 93, 96), 0.1f);
			animation->AddClip(clip);
		}
		//Walk to Down : 5 //  완료, 체크 전
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 49, 12, 64), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 19, 48, 29, 62), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 48, 45, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 50, 49, 60, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 48, 76, 64), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 82, 48, 92, 64), 0.1f);
			animation->AddClip(clip);
		}
	}


	// roll
	{   
		// Roll To UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right_UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right_down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}

	}

	// Nuckback
	{
		// Nuckback To UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Nuckback To Right_UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Nuckback To Right
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Nuckback To Right_down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Nuckback To Down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}

	}
	// death : 4
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
		animation->AddClip(clip);
	}
	// Charge
	{
		// Charge To UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Charge To Right_UP
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Charge To Right
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Charge To Right_down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
		// Charge To Down
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
			animation->AddClip(clip);
		}
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

	animation->SetPosition(position);
	animation->Play(bMove ? 1 : 0);

	animation->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	animation->Render();

}