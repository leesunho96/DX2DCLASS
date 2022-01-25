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
	
	void SetActivate();
private:

	void ActionWhileIdle();
	void ActionWhileChangeDegree();
	void ActionWhileAttack();
	void ActionWhilePlayingOtherAnimation();
	void ActionWhileGoesToIdle();
	void BehaviorTree();
public:
private:
	bool bIsActivate = false;
	int iPlayAnimatnion;
	ArmType armtype;
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 targetPosition;
	vector <function<void(void)>> actions;
	StopWatch stopwatch;
	unsigned char PresentState = 0;
	
};