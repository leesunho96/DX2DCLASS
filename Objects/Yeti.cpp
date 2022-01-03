#include "stdafx.h"
#include "Yeti.h"
#include "SnowBall.h"
#include "Icycle.h"
#include "Player.h"
#include "Arrow.h"

#define DIRECTION_UP 0
#define DIRECTION_RIGHTUP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_RIGHTDOWN 3
#define DIRECTION_DOWN 4

extern ActorsData* actorsdata;

Yeti::Yeti(D3DXVECTOR2 position, D3DXVECTOR2 scale): stopwatch(StopWatch()), position(position)
{
	wstring TextureFile = Textures + L"TianSouls/yeti.png";
	wstring ShaderFile = Shaders + L"009_Sprite.fx";

	animation = new Animation();
	Clip* clip;

	// Idle 0
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 302, 702, 370, 767), 999.0f);
		animation->AddClip(clip);
	}
	// Standing (Begin Start) 1
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 302, 702, 370, 767), 1.0f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 203, 697, 273, 767), 1.0f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 11, 697, 84, 767), 1.0f);
		animation->AddClip(clip);
	}
	// Throw Snow Ball To Up 2
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 4  , 223, 91 , 287), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 221, 187, 287), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 196, 221, 281, 287), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 306, 200, 366, 287), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 397, 208, 466, 287), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 493, 223, 562, 287), 0.1f);
		animation->AddClip(clip);
	}
	// Throw Snow Ball To RightUp 3
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 26 , 320, 86 , 382), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 123, 320, 181, 382), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 219, 320, 278, 382), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 312, 294, 365, 382), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 409, 294, 477, 382), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 505, 317, 573, 382), 0.1f);
		animation->AddClip(clip);

	}
	// Throw Snow Ball To Right 4 
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 28 , 30, 80 , 93), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 123, 30, 175, 93), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 220, 30, 271, 93), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 312, 3 , 360, 93), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 413, 21, 465, 93), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 510, 30, 560, 93), 0.1f);
		animation->AddClip(clip);
	}
	// Throw Snow Ball To RightDown 5 
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 16 , 415, 83 , 480), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 113, 415, 178, 480), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 210, 415, 274, 480), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 310, 387, 362, 480), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 406, 398, 476, 480), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 501, 415, 569, 480), 0.1f);
		animation->AddClip(clip);
	}
	// Throw Snow Ball To Down 6
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 3  , 222, 90 , 288), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 100, 222, 187, 288), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 197, 222, 281, 288), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 307, 201, 364, 288), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 396, 208, 467, 288), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 494, 222, 562, 288), 0.1f);
		animation->AddClip(clip);
	}

	// Roll To Up 7
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 128, 655, 190), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 688, 128, 750, 190), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 784, 128, 846, 190), 0.1f);
		animation->AddClip(clip);
	}
	// Roll To RightUp 8 
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 320, 655, 381), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 688, 320, 750, 381), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 784, 320, 846, 381), 0.1f);
		animation->AddClip(clip);
	}
	// Roll To Right 9
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 32, 655, 94), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 688, 32, 750, 94), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 784, 32, 846, 94), 0.1f);
		animation->AddClip(clip);
	}
	// Roll To RightDown 10
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 415, 655, 478), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 688, 415, 750, 478), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 784, 415, 846, 478), 0.1f);
		animation->AddClip(clip);
	}
	// Roll To Down 11
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 223, 655, 286), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 688, 223, 750, 286), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 784, 223, 846, 286), 0.1f);
		animation->AddClip(clip);
	}

	// Die While See Up 12
	{
		clip = new Clip(PlayMode::Stop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 391, 604, 473, 670), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 496, 613, 557, 670), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 595, 634, 652, 670), 0.1f);
		animation->AddClip(clip);
	}
	// Die While See RightUp 13
	{
		clip = new Clip(PlayMode::Stop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 412, 801, 470, 861), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 496, 793, 560, 850), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 593, 805, 656, 850), 0.1f);		
		animation->AddClip(clip);
	}
	// Die While See Right 14
	{
		clip = new Clip(PlayMode::Stop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 412, 515, 463, 574), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 493, 521, 570, 574), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 589, 543, 668, 574), 0.1f);
		animation->AddClip(clip);
	}
	// Die While See RightDown 15
	{
		clip = new Clip(PlayMode::Stop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 404, 898, 467, 954), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 499, 905, 565, 954), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 594, 909, 660, 954), 0.1f);
		animation->AddClip(clip);
	}
	// Die While See Down 16
	{
		clip = new Clip(PlayMode::Stop);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 389, 707, 475, 765), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 495, 718, 561, 954), 0.1f);
		clip->AddFrame(new Sprite(TextureFile, ShaderFile, 591, 718, 656, 954), 0.1f);
		animation->AddClip(clip);
	}


	// 메모리 풀 이용하지 않고, 각 클래스 내부에 validate/invalidate 변수 이용하여 객체 생성/소멸 하지 않고 이용
	for (size_t i = 0; i < 5; i++)
	{
		snowballs[i] = new SnowBall();
		snowballs[i]->SetPlayer(actorsdata->GetPlayerData());
		icycles[i] = new Icycle(Math::Random(0, 3), actorsdata->GetPlayerData());
	}

	// 해당 클래스 연결용 데이터 등록
	actorsdata->SetData(this);



	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR2(1, 1);
	presentDirection = D3DXVECTOR2(0, 0);
	animation->SetPosition(position);
	animation->Play(0);
	
}

Yeti::~Yeti()
{
	for (auto a : snowballs)
	{
		SAFE_DELETE(a);
	}

	for (auto a : icycles)
	{
		SAFE_DELETE(a);
	}
	SAFE_DELETE(animation);
}

void Yeti::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	int iLocalpresentdirection;
	if (PresentState == AICheck)
	{
		ActionWhileAICheck();
	}
	else
	{
		if (PresentState == Idle)
		{
			iPlayAnimationNum = 0;
		}
		else if (PresentState == Standing)
		{
			iPlayAnimationNum = 1;
		}
		else if (PresentState == Throwing_SnowBall)
		{
			if (stopwatch.IsOver())
			{
				ResetSnowBallData();
			}
			if (stopwatch.IsOver(iPresentBallNum * 0.5f))
			{
				ValidateSnowball();
			}

			// animationplaynum / rotation 값 설정 위한 메소드
			iLocalpresentdirection = GetDirectionVectorToGeneralIntValues(presentDirection);
			rotation = GetRotationDegreeFromDirectionVector(presentDirection);




		}
		else if (PresentState == Roll)
		{

		}
		else if (PresentState == Die)
		{

		}
	}


	stopwatch.Update();
	animation->Update(V, P);
	animation->SetPosition(position);
	animation->SetRotationDegree(rotation);
	animation->Play(iPlayAnimationNum);
}

void Yeti::ValidateSnowball()
{
	snowballs[iPresentBallNum]->SetValid();
	snowballs[iPresentBallNum]->ResetPosition(animation->GetSprite()->Position() + presentDirection * 50.0f);
	snowballs[iPresentBallNum]->SetDirection(presentDirection);
	iPresentBallNum++;
}

D3DXVECTOR3 Yeti::GetRotationDegreeFromDirectionVector(D3DXVECTOR2 direction)
{
	D3DXVECTOR3 result;
	if (direction.x >= -0.3f && direction.x <= 1.0f)
	{
		result = D3DXVECTOR3(0, 0, 0);
	}
	else if (direction.x >= -1.0f && direction.x < -0.3f)
	{
		result = D3DXVECTOR3(0, 180, 0);
	}
	return result;
}

int Yeti::GetDirectionVectorToGeneralIntValues(D3DXVECTOR2 direction)
{
	// TO UP
	if (direction.x >= -0.3f && direction.x <= 0.3f
		&& presentDirection.y > 0)
	{
		return DIRECTION_UP;
	}
	// TO Down
	else if (direction.x >= -0.3f && direction.x <= 0.3f
		&& presentDirection.y < 0)
	{
		return DIRECTION_DOWN;
	}
	// TO RIght_Up
	else if (direction.x > 0.3f && direction.x < 0.7f
		&& presentDirection.y > 0)
	{
		return DIRECTION_RIGHTUP;
	}
	// TO Right_Down
	else if (direction.x > 0.3f && direction.x < 0.7f
		&& presentDirection.y < 0)
	{
		return DIRECTION_RIGHTDOWN;
	}
	// TO Right
	else if (direction.x >= 0.7f && direction.x <= 1.0f)
	{
		return DIRECTION_RIGHT;
	}
	// TO Left_Up
	else if (direction.x < -0.3f && direction.x < -0.7f &&
		presentDirection.y > 0)
	{
		return DIRECTION_RIGHTUP;
	}
	// TO Left_Down
	else if (direction.x < -0.3f && direction.x < -0.7f &&
		presentDirection.y < 0)
	{
		return DIRECTION_RIGHTDOWN;
	}
	// To Left
	else if (direction.x <= -0.7f && direction.x >= -1.0f)
	{
		return DIRECTION_RIGHT;
	}
}

void Yeti::ResetSnowBallData()
{
	PresentState = AICheck;
	for (auto a : snowballs)
	{
		a->SetInvalid();
	}
	iPresentBallNum = 0;
}

void Yeti::ActionWhileAICheck()
{
	PresentState = BehavierTree();
	D3DXVECTOR2 tempVec(actorsdata->GetPlayerData()->GetSprite()->Position() - this->animation->GetSprite()->Position());
	D3DXVec2Normalize(&presentDirection, &tempVec);
	stopwatch.ResetTimer();
	stopwatch.SetTimer(1.5f);
}

void Yeti::Render()
{
	animation->Render();
}

Sprite * Yeti::GetSprite()
{
	return animation->GetSprite();
}

unsigned char Yeti::BehavierTree()
{
	unsigned char result;

	// first node => 최초 실행시
	if (iPresentTurnNum == 0)
	{
		result = Throwing_SnowBall;
		iSnowballTurnNum++;
		iPresentTurnNum++;
	}
	// 두번째 노드. 현재 구르기/눈덩이 던지기 횟수 이용해서 다음 행동 산출.
	else
	{
		//int maxprecentage = iPresentTurnNum;
		//int randompercentage = Math::Random(0, maxprecentage);
		//
		//if (iRollTurnNum > randompercentage)
		//{
		//	result = Throwing_SnowBall;
		//}
		//else
		//{
		//	result = Roll;
		//}
		result = Throwing_SnowBall;
	}
	return result;
}

void Yeti::ApplyDamege(Sprite * sprite)
{
	if (PresentState == Idle)
	{
		PresentState = Standing;
		return;
	}
	if (PresentState = Roll)
		return;
	Arrow* arrowsprite = actorsdata->GetPlayerData()->GetArrowSprite();

	if (arrowsprite->GetSprite()->OBB(this->animation->GetSprite()))
	{
		PresentState = Die;
	}
}

