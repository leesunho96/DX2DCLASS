#pragma once
#include "Draws/Rect.h"

class Enemy;

class Player :
	public Rect
{
public:
	int deathCount = 0;
	const int maxJump = 3;
	int presentJump = 0;
public:
	Player(wstring shaderFile, wstring imgFile);
	Player(wstring shaderFile, wstring imgFile, D3DXVECTOR2 position,
		D3DXVECTOR2 scale);
	virtual ~Player();


	void Update() override;
	void StartJump();
	void EndJump();

	bool CollisionTest(vector<Enemy*>& input);
private:
	float speed;
	
	float velocity;
	float gravity;
	bool bOnGround;// ���� �ִ��� Ȯ���ϱ� ����.


};

