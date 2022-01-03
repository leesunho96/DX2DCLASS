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

private:

public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 presentDirection;

	bool bIsAttacked = false;
	bool bIsPlayingOtherAnimation = false;


	const static unsigned char Idle = 0;
	const static unsigned char Standing = 1 << 1;
	const static unsigned char Throwing_SnowBall = 1 << 2;
	const static unsigned char Roll = 1 << 3;
	const static unsigned char Die = 1 << 4;
	const static unsigned char AICheck = 1 << 5;
	// char : 8ºñÆ®
	// 00000000 : Idle
	// 00000001 : Standing
	// 00000010 : Throwing Snowball
	// 00000100 : Roll
	// 00001000 : Die
	// 00010000 : GetAiCheck
	// 00100000 : 
	// 01000000 :
	// 10000000 : 
	unsigned char PresentState = Idle;
		
	
	
	int iPlayAnimationNum = 0;
	int iSnowballTurnNum = 0;
	int iRollTurnNum = 0;

	Animation* animation;
	SnowBall* snowballs[5];
	Icycle* icycles[5];
};