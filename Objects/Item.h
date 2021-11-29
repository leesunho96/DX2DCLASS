#pragma once

class Sprite;

class Item
{
public:
	Item(int type);
	~Item();

	virtual void Update(D3DXMATRIX&V, D3DXMATRIX& P);
	virtual void Render();

	void SetPosition(D3DXVECTOR2 position) { this->position = position; };

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	int type;
	float speed = 200.0f;

};