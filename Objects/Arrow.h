#pragma once

class Arrow
{
public:
	Arrow(wstring spriteFile, wstring shaderFile);
	~Arrow();
	void SetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosition() { return position; };
	Sprite* GetSprite() { return sprite; };
	D3DXVECTOR2 GetTextureSize() { return sprite->TextureSize(); };
	void SetActivate(bool input) { isActivate = input; };

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	
private:
	Sprite* sprite;
	D3DXVECTOR2 position;
	bool isActivate = false;
};