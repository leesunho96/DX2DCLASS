#pragma once

class Bullet
{
public:
	Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	~Bullet();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; };
	D3DXVECTOR2 Position() { return position; };

private:
	
	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0);

};