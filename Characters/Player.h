#pragma once
#include "Viewer/IFollowing.h"
#include "Character.h"
class Arrow;
class StopWatch;

class Player : public IFollowing, public Character
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	//virtual vector<Sprite*> GetSprite() override { };
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void ApplyDamege(Sprite* sprite) override;
	virtual D3DXVECTOR2 GetOffset() override { return focusoffset; }; ;
	virtual bool IsAttackable() { return !isRoll; };
	virtual bool IsIdle() { return playAnimation == 0; };
	
	
	bool GetPlayerIsDied() { return bGetDamege; };
	void ResetPlayer(D3DXVECTOR2 &position);
	void GetArrow();
	Arrow* GetArrowSprite() { return arrow; };
	void SetPlayerGetArrow();
	void SetPlayerCantGetArrow();
	void SetNuckBack(D3DXVECTOR2 position);

private:
	void GetAppropriateAnimNumAndRotation(D3DXVECTOR3 &RightRotation, D3DXVECTOR3 &LeftRotation);
	void ActWhileNuckBack(D3DXVECTOR2 &position);
	void PlayerMove(D3DXVECTOR2 &position, float timerelapse, D3DXMATRIX & V, D3DXMATRIX & P);
	void ActWhileNotApplyDamege(D3DXVECTOR2 &position, D3DXMATRIX & V, D3DXMATRIX & P);
	void ActWhilePlayingOtherAnimation();
	void ResetStopWatch();
	void SetAnimationFromDirectionAndSpace(D3DXVECTOR2 &direction, int &playAnimation, bool isRoll);
	void SetKeyInputToIsRoll(unsigned char forwardflag, bool &isRoll);
	void SetKeyInputToDirectionVector(unsigned char forwardflag, D3DXVECTOR2 &direction);
	void GetKeyInputByBitFlag(unsigned char &forwardflag);
	D3DXVECTOR2 GetArrowPosition();
	D3DXVECTOR2 GetArrowDirection();

private:
	
	float moveSpeed;
	Animation* animation;
	Sprite* DiedImage;
	Arrow* arrow;
	StopWatch* Cstopwatch;
	D3DXVECTOR2 focusoffset;
	D3DXVECTOR2 direction = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 pastDirection = D3DXVECTOR2(0, 0);

	bool bIsGetFarDisatance = false;
	bool isRoll = false;
	bool bIsHaveArrow = true;
	bool bIsReTrivingArrow = false;
	bool bGetDamege = false;
	bool bIsNuckBack = false;
	bool isplayingOtherAnimation = false;
	bool bIsOverlap = false;
	bool isCharge = false;
	bool bIsInvincible = false;

	float stopwatch = 0.0f;
	float stopTime = 0.0f;
	float presentDistance = 999.9f;
	float pastFarDistance = 999.9f;
	int playAnimation = 0;

	vector<float> pastFarDistanceVector;
};