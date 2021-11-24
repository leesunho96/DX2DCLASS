#pragma once

class Coin
{
public:

	Coin(D3DXVECTOR2 Position);
	~Coin();

private:
	Animation* animation;
	D3DXVECTOR2 Position;

};