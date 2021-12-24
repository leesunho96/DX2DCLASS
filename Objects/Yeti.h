#pragma once

class Yeti
{

public:
	Yeti(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Yeti();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:

public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	int iPlayAnimationNum = 0;

	Animation* animation;
};