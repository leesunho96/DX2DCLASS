#pragma once

class Goomba
{

public:
	Goomba(float fStartXpos, float fEndXPos);
	~Goomba();

	void Update(D3DXMATRIX&V, D3DXMATRIX& P);
	void Render();

private:
	Animation* animation;
	float fStartXpos, fEndXpos;
	D3DXVECTOR2 position;
	bool isToRight = true;
	bool isOverlap = false;
	float elapseTime = 0.0f;
	void ApplyDamege();
};