#pragma once

class Sprite;

class Yeti
{

public:
	Yeti(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Yeti();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	
	void ApplyDamage(Sprite* sprite);

private:

public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 presentDirection;


	bool bIsAttacked = false;
	int iPlayAnimationNum = 0;

	Animation* animation;
};