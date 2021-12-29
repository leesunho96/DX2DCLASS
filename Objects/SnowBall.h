#pragma once

class SnowBall
{
public:
	SnowBall();
	~SnowBall();
	void Update(D3DXMATRIX&V, D3DXMATRIX& P);
	void Render();
	void SetValid() { bIsValid = true; };
	void SetInvalid() { bIsValid = false; };
	void SetDirection(D3DXVECTOR2 direction) { this->direction = direction; };

private:

public:
private:
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 direction;
	bool bIsValid = false;
	int iPlayAnimationNum = 0;
};