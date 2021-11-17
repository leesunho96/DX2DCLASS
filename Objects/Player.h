#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void StartJump();

private:
	float moveSpeed;
	D3DXVECTOR2 focusoffset;
	float velocity = 0.0f;
	float gravity = -0.0001f;
	float fBottomY = 50.0f;
	bool bOnGround = false;
	bool bOnSecondFloor = false;
	bool bIsJumpable = false;
	D3DXVECTOR2 position;
	Animation* animation;
private:
	void KeyInput(D3DXVECTOR2& position, bool& bMove);
	void CheckPosition(D3DXVECTOR2& position);
	//bool isOverlapBox();
	//bool isOverBox(float fPositonY);
	//bool isUnderBox(float fPositionY);
};