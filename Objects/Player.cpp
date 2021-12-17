#include "stdafx.h"
#include "Objects/Player.h"
#include "Systems/CollisionSystem.h"

extern CollisionSystem* collisionsystem;

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
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 49, 13, 64), 0.3f);
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
		// Roll To UP : 6 // 완료, 체크 전.
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 18, 108, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 115, 20, 125, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 130, 23, 141, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 146, 22, 157, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 163, 20, 173, 31), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 178, 19, 189, 28), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right_UP : 7 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 98, 104, 111), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 112, 101, 124, 111), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 130, 103, 141, 111), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 101, 157, 111), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 163, 104, 173, 111), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 178, 96, 190, 110), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right : 8 // 완료, 체크 전
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 3, 108, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 114, 5, 126, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 130, 7, 142, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 146, 5, 156, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 161, 6, 174, 16), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 177, 0, 189, 12), 0.1f);
			animation->AddClip(clip);
		}
		// Roll To Right_down : 9 // 완료/체크전
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 82, 107, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 112, 84, 124, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 129, 88, 140, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 85, 157, 96), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 87, 174, 95), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 179, 80, 190, 93), 0.1f);

			animation->AddClip(clip);
		}
		// Roll To Down : 10 
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 49, 108, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 115, 53, 125, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 55, 141, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 44, 157, 63), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 54, 173, 61), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 178, 50, 188, 59), 0.1f);

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
	// death : 4 // 완성 체크전.
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 370, 50, 381, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 355, 50, 365, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 339, 50, 349, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 323, 50, 333, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 307, 50, 317, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 290, 50, 300, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 275, 50, 285, 64), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 343, 50, 353, 64), 0.1f);
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


// 외적으로 선분 교점 구하기.
//https://bowbowbow.tistory.com/17

// bitflag
// https://ansohxxn.github.io/cpp/chapter3-3/
bool isonUpperSide = false;
void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->GetPosition();
	D3DXVECTOR2 pastPosition = position;
	D3DXVECTOR2 textureSize = animation->TextureSize();
	Sprite* presentSprite = animation->GetSprite();

	float timerelapse = Timer->Elapsed();

	// 구르기, 피격 등으로 애니메이션 출력중인 경우
	if (!isplayingOtherAnimation)
	{
		// bitflag 이용.
		direction = D3DXVECTOR2(0, 0);
		unsigned char forwardflag = 0;
		GetKeyInputByBitFlag(forwardflag);	// 현재 입력된 키를 확인 한 후, 해당 키에 따라 forwardflag에 비트 삽입
		SetKeyInputToDirectionVector(forwardflag, direction); // 입력된 비트에 따라 벡터 결정. 
		SetKeyInputToIsRoll(forwardflag, isRoll); // 현재 스페이스바 키가 입력되었는지 확인, isroll 변수 세팅
		SetAnimationFromDirectionAndSpace(direction, playAnimation, isRoll); // 현재 방향벡터와 isroll변수로 애니메이션 세팅.
		D3DXVec2Normalize(&direction, &direction); // 현재 방향 벡터를 정규화.

		pastDirection = direction == D3DXVECTOR2(0, 0) ? pastDirection : direction;
	}
	else
	{
		stopwatch += Timer->Elapsed();
		if (isRoll)
		{

		}

		if (stopwatch > stopTime)
		{
			ResetStopWatch();
			isRoll = false;
		}
	}
	position += direction * timerelapse * moveSpeed;
	//presentSprite->Position(position);
	animation->SetPosition(position);
	
	while (collisionsystem->CollisionTest(animation->GetSprite()))
	{
		//if (direction = D3DXVECTOR2(0, 0))
		//{
		//	float degree = collisionsystem->GetDegree(animation->GetSprite());
		//	//position -= pastDirection * timerelapse * moveSpeed;			
		//	position -= D3DXVECTOR2(cosf(degree), sinf(degree)) * timerelapse * moveSpeed;
		//}
		//else
		
		position -= pastDirection * timerelapse * moveSpeed;		
		animation->SetPosition(position);
		animation->Update(V, P);
		//presentSprite->Position(position);
	}
	animation->SetPosition(position);
	animation->Update(V, P);
	animation->Play(playAnimation);

}

void Player::ResetStopWatch()
{
	stopTime = 0.0f;
	stopwatch = 0.0f;
	isplayingOtherAnimation = false;
}

void Player::SetAnimationFromDirectionAndSpace(D3DXVECTOR2 &direction, int &playAnimation, bool isRoll)
{
	if (direction.x == 0 && direction.y == 0)
	{
		playAnimation = 0;
		animation->SetRotationDegree(0, 0, 0);
	}
	else if (direction.x == 0 && direction.y == 1)
	{
		playAnimation = 1;
		animation->SetRotationDegree(0, 0, 0);
	}
	else if (direction.x == 0 && direction.y == -1)
	{
		playAnimation = 5;
		animation->SetRotationDegree(0, 0, 0);
	}
	else if (direction.x == 1 && direction.y == 0)
	{
		playAnimation = 3;
		animation->SetRotationDegree(0, 0, 0);
	}
	else if (direction.x == -1 && direction.y == 0)
	{
		playAnimation = 3;
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (direction.x > 0 && direction.y > 0)
	{
		playAnimation = 2;
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (direction.x > 0 && direction.y < 0)
	{
		playAnimation = 4;
		animation->SetRotationDegree(0, 180, 0);
	}
	else if (direction.x < 0 && direction.y > 0)
	{
		playAnimation = 2;
		animation->SetRotationDegree(0, 0, 0);
	}
	else if (direction.x < 0 && direction.y < 0)
	{
		playAnimation = 4;
		animation->SetRotationDegree(0, 0, 0);
	}
	if (isRoll)
	{
		playAnimation += 5;
	}
}

void Player::SetKeyInputToIsRoll(unsigned char forwardflag, bool &isRoll)
{
	if ((forwardflag & PressSpace)
		&& (direction != D3DXVECTOR2(0, 0)))
	{
		isRoll = true;
		stopTime = 0.6f;
		isplayingOtherAnimation = true;
	}
}


void Player::SetKeyInputToDirectionVector(unsigned char forwardflag, D3DXVECTOR2 &direction)
{
	if (forwardflag & PressA)
	{
		direction.x += -1;
	}
	if (forwardflag & PressD)
	{
		direction.x += 1;
	}
	if (forwardflag & PressW)
	{
		direction.y += 1;
	}
	if (forwardflag & PressS)
	{
		direction.y += -1;
	}

}

void Player::GetKeyInputByBitFlag(unsigned char &forwardflag)
{
	if (Key->Press('A'))
	{
		forwardflag |= PressA;

	}
	if (Key->Press('D'))
	{
		forwardflag |= PressD;

	}
	if (Key->Press('W'))
	{
		forwardflag |= PressW;
	}
	if (Key->Press('S'))
	{
		forwardflag |= PressS;
	}
	if (Key->Press(VK_SPACE))
	{
		forwardflag |= PressSpace;
	}
}

void Player::Render()
{
	D3DXVECTOR2 position = animation->GetPosition();
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	ImGui::LabelText("Position :", "%.0f, %.0f", position.x, position.y);
	ImGui::LabelText("IsOnUpperSide : ", "%.0f", isonUpperSide);
	animation->Render();
}