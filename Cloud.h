#pragma once
#include "Draws/Rect.h"
class Cloud :
	public Rect
{
	int respawnTime;
	bool isStop = true;
	int coolTime = respawnTime;
	float speed = Math::Random(0.01f, 0.2f);
public:
		Cloud(wstring imgFile, D3DXVECTOR2 scale = D3DXVECTOR2(100, 100), D3DXVECTOR2 position = D3DXVECTOR2(Width + 100, 10)) :
		Rect(L"../_Shaders/007_Texture.fx",
			imgFile,
			position,
			scale),
		respawnTime(Math::Random(10000, 50000)) {};

	void setPosition(D3DXVECTOR2& position);
	void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;

};

