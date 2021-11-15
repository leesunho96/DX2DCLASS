#pragma once

class Player
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void StartJump();

private:
	float moveSpeed;
	float velocity = 0.0f;
	float gravity = -0.001f;
	float fBottomY = 50.0f;
	bool bOnGround = false;
	bool bOnSecondFloor = false;
	bool bIsJumpable = false;

	
	Animation* animation;
private:
	bool isOverlapBox();
	bool isOverBox(float fPositonY);
	bool isUnderBox(float fPositionY);
};