#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	
	Sprite* GetSprite() { return animation->GetSprite(); };
	
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void ResetStopWatch();
	void SetAnimationFromDirectionAndSpace(D3DXVECTOR2 &direction, int &playAnimation, bool isRoll);
	void SetKeyInputToIsRoll(unsigned char forwardflag, bool &isRoll);
	void SetKeyInputToDirectionVector(unsigned char forwardflag, D3DXVECTOR2 &direction);
	void GetKeyInputByBitFlag(unsigned char &forwardflag);
	void Render();

private:
	float moveSpeed;
	Animation* animation;
	D3DXVECTOR2 focusoffset;
	bool isplayingOtherAnimation = false;
	D3DXVECTOR2 direction = D3DXVECTOR2(0, 0);
	float stopwatch = 0.0f;
	float stopTime = 0.0f;
	int playAnimation = 0;
	bool isRoll = false;
	float pastFarDistance = 999.9f;
	float presentDistance = 999.9f;
	bool bIsOverlap = false;
	bool bIsGetFarDisatance = false;
	vector<float> pastFarDistanceVector;
	D3DXVECTOR2 pastDirection = D3DXVECTOR2(0, 0);
};