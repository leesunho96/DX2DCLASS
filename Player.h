#pragma once
#include "Draws/Rect.h"


class Player :
	public Rect
{
public:
	Player(wstring shaderFile);
	Player(wstring shaderFile, D3DXVECTOR2 position,
		D3DXVECTOR2 scale, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	virtual ~Player();

	
	void Update() override;
	void MoveLeft();
	void MoveRight();

	void AutoMoveStart();

	void Speed(float val) { speed = val; };
	float Speed() { return speed; };

	void StartJump();
	void EndJump();
private:

	bool isAutoMove = false;
	bool isToRight = true;
	bool isSecondJump = false;
	float speed;
	float secondJumpStartY = 0.0f;

	float velocity;
	float gravity;
	bool bOnGround;// 땅에 있는지 확인하기 위함.

private:
	bool isTouchRightWall();
	bool isTouchLeftWall();
};

