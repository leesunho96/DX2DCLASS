#pragma once
#include "Character.h"

class SnowBall;
class Icycle;

class Yeti : public Character
{

public:
	Yeti(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Yeti();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void ApplyDamege(Sprite* sprite) override;
	virtual Sprite* GetSprite() override;
	virtual D3DXVECTOR2 GetOffset() override { return D3DXVECTOR2(0, 0); };

	virtual bool IsAttackable() override;
	virtual bool IsIdle() override { return PresentState == (unsigned char)0; }


private:
	void SetPositionRotationScalePlayAnimationUpdate(D3DXMATRIX & V, D3DXMATRIX & P);
	bool IsActorsToRight(D3DXVECTOR2 &direction);
	void ActionWhileDead();
	void SetDirectionRotationAnimationNum(int &iLocalpresentdirection, int i);
	void ActivateIcycles();
	void ActBeforeAICheck();
	// �ൿ ��ȯ.
	unsigned char BehavierTree();
	// ���⺤�͸� �Ϲ�ȭ�� int ������ ��ȯ. => 8�������� ��ȯ, �¿� degree�� GetRotationDegreeFromDirectionVector() ����.
	int GetDirectionVectorToGeneralIntValues(D3DXVECTOR2 direction);
	// ���� ���⺤�͸� �Է¹����� �׿� ���� ��/�� degree �� ��ȯ.
	D3DXVECTOR3 GetRotationDegreeFromDirectionVector(D3DXVECTOR2 direction);

	// ������ Ȱ��ȭ �޼ҵ�.
	void ValidateSnowball();
	// ������ ��ü�� �ʱ�ȭ.
	void ResetSnowBallData();
	// AI ����� �Ͼ�� �޼ҵ�
	void ActionWhileAICheck();
	// ���� �÷��̾� ���������� ���� ���ϴ� �޼ҵ�
	void GetPresentDirectionToPlayer();
	void PlayerMove(D3DXVECTOR2 &position, float timerelapse, D3DXVECTOR2 direction, float Speed, D3DXMATRIX & V, D3DXMATRIX & P);
	void SetHitboxPosition(RECT& rect, int iPlayAnimation);
public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 presentDirection;
	RECT hitbox;

	bool bIsAttacked = false;
	bool bIsPlayingOtherAnimation = false;
	bool bIsGetArrowPos = false;


	//const static unsigned char Idle = 0;
	//const static unsigned char Standing = 1 << 1;
	//const static unsigned char Throwing_SnowBall = 1 << 2;
	//const static unsigned char Roll = 1 << 3;
	//const static unsigned char Die = 1 << 4;
	//const static unsigned char AICheck = 1 << 5;
	// char : 8��Ʈ
	// 00000000 : Idle
	// 00000001 : Standing
	// 00000010 : Throwing Snowball
	// 00000100 : Roll
	// 00001000 : Die
	// 00010000 : GetAiCheck
	// 00100000 : 
	// 01000000 :
	// 10000000 : 
	unsigned char PresentState = 0;// Idle;
		
	
	
	int iPlayAnimationNum = 0;
	int iPresentTurnNum = 0;
	int iSnowballTurnNum = 0;
	int iRollTurnNum = 0;
	int iPresentBallNum = 0;

	Animation* animation;
	SnowBall* snowballs[3];
	Icycle* icycles[5];
	StopWatch stopwatch;
};