#pragma once


class Ghost
{
public:
	Ghost(D3DXVECTOR2 position);
	~Ghost();


	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();


private:
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	
	void InitializeAnimation();

};