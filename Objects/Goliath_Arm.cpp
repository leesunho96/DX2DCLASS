#include "stdafx.h"
#include "Goliath_Arm.h"
#include "Systems/StopWatch.h"

#define IDLE 0
#define CHANGEDEGREE 1
#define ATTACK 2
#define GOESTOIDLE 3
#define CHANGEDEGREETIME 0.9f
#define ATTACKTIME 0.6f
extern ActorsData* actorsdata;

Goliath_Arm::Goliath_Arm(ArmType armtype, D3DXVECTOR2 position) : armtype(armtype), position(position), stopwatch(StopWatch()), rotation(D3DXVECTOR3(0, 0, 0)), scale(D3DXVECTOR2(1, 1))
{
	wstring texture = Textures + L"/TianSouls/gol_lath.png";
	wstring shader = Shaders + L"/009_Sprite.fx";

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
			clip->AddFrame(new Sprite(texture, shader, 390, 270, 440, 305), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 455, 265, 495, 305), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), 0.3f);
		}
		animation->AddClip(clip);
		// arm Attack
		{
			clip = new Clip(PlayMode::Stop);
			clip->AddFrame(new Sprite(texture, shader, 330, 260, 375, 295), 0.3f);
			clip->AddFrame(new Sprite(texture, shader, 260, 270, 300, 310), 0.3f);
		}
		animation->AddClip(clip);
	}

	rotation = armtype == ArmType::Left ? D3DXVECTOR3(0, 0, 0) : D3DXVECTOR3(0, 180, 0);
	scale = D3DXVECTOR2(1, 1);
	iPlayAnimatnion = IDLE;

	actions.push_back(bind(&Goliath_Arm::ActionWhileIdle, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileChangeDegree, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileAttack, this));
	actions.push_back(bind(&Goliath_Arm::ActionWhileGoesToIdle, this));
	
}

Goliath_Arm::~Goliath_Arm()
{
	SAFE_DELETE(animation);
}

void Goliath_Arm::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!bIsActivate)
	{
		InitializeScaleRotationPositionPlayAnimNum(V, P);
		return;
	}
	stopwatch.Update();
	actions[PresentState]();
	InitializeScaleRotationPositionPlayAnimNum(V, P);
}


void Goliath_Arm::Render()
{
	animation->Render();
}

void Goliath_Arm::InitializeScaleRotationPositionPlayAnimNum(D3DXMATRIX & V, D3DXMATRIX & P)
{
	animation->SetPosition(position);
	animation->SetRotation(rotation);
	animation->SetScale(scale);
	animation->Update(V, P);
	animation->Play(iPlayAnimatnion);

void Goliath_Arm::SetActivate()
{
	bIsActivate = true;
}

void Goliath_Arm::ActionWhileIdle()
{

}

void Goliath_Arm::ActionWhileChangeDegree()
{
}

void Goliath_Arm::ActionWhileAttack()
{
}

void Goliath_Arm::ActionWhilePlayingOtherAnimation()
{
}

void Goliath_Arm::ActionWhileGoesToIdle()
{
}

void Goliath_Arm::BehaviorTree()
{


}
