#pragma once
#include "Draws/Rect.h"
class Ground :
	public Rect
{
private :
	const D3DXVECTOR2 baseLocation;
public:
	Ground() : Rect(L"../_Shaders/007_Texture.fx", L"../_Textures/Trex/Floor.png",
		D3DXVECTOR2(Width / 2, 10), 
		D3DXVECTOR2(Width, 10)),
		baseLocation(D3DXVECTOR2(Width / 2, 10)) {};
	Ground(D3DXVECTOR2 position) :
		Rect(L"../_Shaders/007_Texture.fx", 
			L"../_Textures/Trex/Floor.png",
			position, D3DXVECTOR2(Width, 10))
		, baseLocation(position) {};

	virtual ~Ground();
	void Move();
	void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
};

