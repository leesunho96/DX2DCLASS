#pragma once
#include "Viewer/IFollowing.h"

class Arrow;

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	
	Sprite* GetSprite() { return animation->GetSprite(); };

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
private:
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
	Arrow* arrow;
	D3DXVECTOR2 focusoffset;
	D3DXVECTOR2 direction = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 pastDirection = D3DXVECTOR2(0, 0);
	bool isplayingOtherAnimation = false;
	bool bIsOverlap = false;
	bool bIsGetFarDisatance = false;
	bool isRoll = false;
	bool isCharge = false;
	bool bIsHaveArrow = true;
	float stopwatch = 0.0f;
	float stopTime = 0.0f;
	float presentDistance = 999.9f;
	float pastFarDistance = 999.9f;
	int playAnimation = 0;
	vector<float> pastFarDistanceVector;
};