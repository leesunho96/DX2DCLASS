#include "stdafx.h"
#include "Goliath_Arm.h"
#include "Systems/StopWatch.h"
#include "Characters/Player.h"


#include "Physics/CollisionDesc.h"
#include "Physics/CollisionSystem.h"

#define IDLE 0
#define CHANGEDEGREE 1
#define ATTACK 2
#define GOESTOIDLE 3
#define CHANGEDEGREETIME 0.6f
#define ATTACKTIME 0.4f
#define GOLIATHMAPSCALE 1.5f
#define FRAMETIME 0.1f

extern ActorsData* actorsdata;
extern CollisionSystem* collisionsystem;

Goliath_Arm::Goliath_Arm(ArmType armtype, D3DXVECTOR2 position, D3DXVECTOR2 scale) : 
	armtype(armtype), position(position), stopwatch(StopWatch()), scale(scale), basePosition(D3DXVECTOR2(0, 120))
{
	wstring texture = Textures + L"/TianSouls/gol_lath.png";
	wstring shader = Shaders + L"/009_Sprite.fx";
	animation = new Animation();
	Clip* clip;
	{
		// arm Idle
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 390, 270, 440, 305), 0.3f);
		}

		animation->AddClip(clip);
		// arm Change Degree
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 390, 270, 440, 305), FRAMETIME);
			clip->AddFrame(new Sprite(texture, shader, 455, 265, 495, 305), FRAMETIME);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), FRAMETIME);
		}
		animation->AddClip(clip);
		// arm Attack
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 330, 260, 375, 295), FRAMETIME);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), FRAMETIME);
		}
		animation->AddClip(clip);

		// arm GoesToIdle
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), FRAMETIME);
			clip->AddFrame(new Sprite(texture, shader, 330, 260, 375, 295), FRAMETIME);
		}
		animation->AddClip(clip);
	}



	
	rotation = armtype == ArmType::Left ? D3DXVECTOR3(0, 0, 0) : D3DXVECTOR3(0, 180, 0);
	availableBoundery = armtype == ArmType::Left ?
		RECT{ -(long)(Width * GOLIATHMAPSCALE * 0.5f) ,(long)(Height * GOLIATHMAPSCALE * 0.5f), (long)(1),-(long)(Height * GOLIATHMAPSCALE * 0.5f) } :
		RECT{ (long)(0), (long)(Height * GOLIATHMAPSCALE * 0.5f), (long)(Width * GOLIATHMAPSCALE * 0.5f) ,-(long)(Height * GOLIATHMAPSCALE * 0.5f) };
	

	scale = D3DXVECTOR2(1, 1);
	iPlayAnimatnion = IDLE;
	animation->SetPosition(position);
	animation->Play(IDLE);

	actions.push_back(bind(&Goliath_Arm::ActionWhileIdle, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileChangeDegree, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileAttack, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileGoesToIdle, this));
	bIsActivate = false;
	animation->DrawBound(true);
}

Goliath_Arm::~Goliath_Arm()
{
	SAFE_DELETE(animation);
}

void Goliath_Arm::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position = animation->GetPosition();
	if (!bIsActivate)
	{
		InitializeScaleRotationPositionPlayAnimNum(V, P);
		return;
	}
	stopwatch.Update();
	actions[PresentState]();
	InitializeScaleRotationPositionPlayAnimNum(V, P);

	CollisionDesc collisiondesc;
	collisiondesc.InitializeCollisionDesc(animation, false, 0);
	collisionsystem->SetCollisionDesc(collisiondesc);
}


void Goliath_Arm::Render()
{
	ImGui::LabelText("Position :", "%.0f, %.0f", position.x, position.y);
	animation->Render();
}

void Goliath_Arm::InitializeScaleRotationPositionPlayAnimNum(D3DXMATRIX & V, D3DXMATRIX & P)
{
	animation->Play(iPlayAnimatnion);
	animation->SetPosition(position);
	animation->SetRotationDegree(rotation);
	animation->SetScale(scale);
	animation->Update(V, P);
}
void Goliath_Arm::SetActivate()
{
	bIsActivate = true;
	BehaviorTree();
}

void Goliath_Arm::ActionWhileIdle()
{
	BehaviorTree();
	iPlayAnimatnion = IDLE;
}

void Goliath_Arm::ActionWhileChangeDegree()
{
	if (stopwatch.IsOver())
	{		
		BehaviorTree();
		return;
	}
	targetPosition = actorsdata->GetPlayerData()->GetBodySprite()->Position();
	D3DXVECTOR2 tempTargetPos = D3DXVECTOR2(0, 200.0f) + targetPosition;
	D3DXVECTOR2 direction = tempTargetPos - position;
	D3DXVec2Normalize(&direction, &direction);	
	position += direction * Timer->Elapsed() * Math::D3DXVEC2GetDistance(position, tempTargetPos) * 3.0f;
	iPlayAnimatnion = CHANGEDEGREE;
}

void Goliath_Arm::ActionWhileAttack()
{
	if (stopwatch.IsOver())
	{		
		BehaviorTree();
	}
	position += D3DXVECTOR2(0, -1) * Timer->Elapsed() * (200.0f / ATTACKTIME);
	iPlayAnimatnion = ATTACK;
	if (actorsdata->GetPlayerData()->GetBodySprite()->OBB(this->animation->GetSprite()))
	{
		((Player*)(actorsdata->GetPlayerData()))->ApplyDamege(this->animation->GetSprite());
	}
}

void Goliath_Arm::ActionWhilePlayingOtherAnimation()
{

}

void Goliath_Arm::ActionWhileGoesToIdle()
{

	if (oppositeArm->GetPresentState() == GOESTOIDLE)
	{
		BehaviorTree();
		return;
	}
	if 
	(		
		(
		/*	((int)(basePosition.x) == (int)(position.x)) &&	
			((int)(basePosition.y) == (int)(position.y))*/

			(position.x >= basePosition.x - 5.0f && position.x <= basePosition.x + 5.0f) &&
			(position.y >= basePosition.y - 5.0f && position.y <= basePosition.y + 5.0f) 
		)
	)
	{
		BehaviorTree();		
	}

	D3DXVECTOR2 direction = basePosition - position;
	D3DXVec2Normalize(&direction, &direction);
	position += direction * Timer->Elapsed() * Math::D3DXVEC2GetDistance(position, basePosition) * 3;
	iPlayAnimatnion = GOESTOIDLE;
}

void Goliath_Arm::BehaviorTree()
{
	D3DXVECTOR2 PlayerPos = actorsdata->GetPlayerData()->GetBodySprite()->Position();
	
	bool isOverlapPlayer = 
		(PlayerPos.x < availableBoundery.right && PlayerPos.x > availableBoundery.left)
			&& 
		(PlayerPos.y < availableBoundery.top && PlayerPos.y > availableBoundery.bottom) 
		? true : false;

	if (isOverlapPlayer)
	{
		switch (PresentState)
		{
		case IDLE:
			//PresentState = CHANGEDEGREE;
			//stopwatch.RetAndSetTimer(CHANGEDEGREETIME);
			SetPresentState(CHANGEDEGREE);
			break;
		case CHANGEDEGREE:
			//PresentState = ATTACK;
			//stopwatch.RetAndSetTimer(ATTACKTIME);
			SetPresentState(ATTACK);
			break;
		case ATTACK:
			//PresentState = CHANGEDEGREE;
			//stopwatch.RetAndSetTimer(CHANGEDEGREETIME);
			SetPresentState(CHANGEDEGREE);
			break;
		case GOESTOIDLE:
			//PresentState = IDLE;
			SetPresentState(IDLE);
			break;
		default:
			break;
		}

	}
	else
	{
		switch (PresentState)
		{
		case IDLE:
			//PresentState = IDLE;
			SetPresentState(IDLE);
			break;
		case CHANGEDEGREE:
			//PresentState = ATTACK;
			//stopwatch.RetAndSetTimer(ATTACKTIME);
			SetPresentState(ATTACK);
		case ATTACK:
			//PresentState = GOESTOIDLE;
			SetPresentState(GOESTOIDLE);
			return;
		case GOESTOIDLE:
			if (oppositeArm->GetPresentState() == GOESTOIDLE)
			{
				//PresentState = ATTACK;
				//stopwatch.RetAndSetTimer(ATTACKTIME);
				SetPresentState(ATTACK);
			}
			else
			{
				//PresentState = IDLE;
				SetPresentState(IDLE);
			}
			break;
		default:
			break;
		}
	}
}

void Goliath_Arm::SetPresentState(unsigned char input)
{
	switch (input)
	{
	case IDLE:
		PresentState = IDLE;
		break;
	case CHANGEDEGREE:
		PresentState = CHANGEDEGREE;
		stopwatch.RetAndSetTimer(CHANGEDEGREETIME);
		break;
	case ATTACK:
		PresentState = ATTACK;
		stopwatch.RetAndSetTimer(ATTACKTIME);
		break;
	case GOESTOIDLE:
		PresentState = GOESTOIDLE;
		//stopwatch.RetAndSetTimer(CHANGEDEGREETIME);
		break;
	default:
		break;
	}
}
