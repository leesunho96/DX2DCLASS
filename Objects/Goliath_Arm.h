#pragma once

class StopWatch;

enum class ArmType
{
	Left = 0, Right
};

class Goliath_Arm
{
public:
	Goliath_Arm(ArmType armtype,D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Goliath_Arm();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void InitializeScaleRotationPositionPlayAnimNum(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

	Sprite* GetSprite() { return animation->GetSprite(); };
	unsigned char GetPresentState() { return PresentState; };
	void SetOppositeArm(Goliath_Arm* oppositeArm) { this->oppositeArm = oppositeArm; };
	void SetActivate();
	void SetInvalidate();
private:

	void ActionWhileIdle();
	void ActionWhileChangeDegree();
	void ActionWhileAttack();
	void ActionWhilePlayingOtherAnimation();
	void ActionWhileGoesToIdle();
	void BehaviorTree();

	void SetPresentState(unsigned char input);
public:
private:
	const D3DXVECTOR2 basePosition;
	bool bIsActivate = false;
	int iPlayAnimatnion;
	ArmType armtype;
	RECT availableBoundery;
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 targetPosition;
	vector <function<void(void)>> actions;
	Goliath_Arm* oppositeArm;
	StopWatch stopwatch;
	unsigned char PresentState = 0;
	
};