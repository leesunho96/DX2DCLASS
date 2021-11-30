#pragma once

//class Sprite;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void SetPosition(D3DXVECTOR2 position);

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	bool GetIsValid() { return isValid; };

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
	bool isValid = true;
};

