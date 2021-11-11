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
	void SetPlaying() { bIsPlaying = true; };
	void ResetClip();
	void Update(D3DXMATRIX&V, D3DXMATRIX&p) override;
	void Render();
	void StartJump();
	void EndJump();
	void SetCrouch();

	bool CollisionTest(vector<Enemy*>& input);
private:
	float speed;

	float velocity;
	float gravity;
	bool bOnGround;// 땅에 있는지 확인하기 위함.
	bool bIsPlaying = true;
	Sprite* presentRenderImage;
	Clip* Walk;
	Clip* Jump;
	Clip* Crouch;
	Clip* Die;
	Clip* PresentClip = nullptr;
private:
	void InitializeClip(std::wstring &shaderFile);


};

