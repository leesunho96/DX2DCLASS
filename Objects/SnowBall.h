#pragma once

class Player;

class SnowBall
{
public:
	SnowBall();
	SnowBall(Player* player);
	~SnowBall();
	void InitializeAnimation();
	void Update(D3DXMATRIX&V, D3DXMATRIX& P);
	void Render();
	void SetValid() { bIsValid = true; };
	void SetInvalid() { bIsValid = false; };
	void SetDirection(D3DXVECTOR2 direction) { this->direction = direction; };
	void SetPlayer(Player* player) { this->player = player; };
	void ResetPosition(D3DXVECTOR2 pos);
	
private:
	void ResetStopwatch();
public:
private:
	Animation* animation;
	StopWatch stopwatch;
	Player* player;
	D3DXVECTOR2 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 direction;
	bool bIsValid = false;
	int iPlayAnimationNum = 0;
};