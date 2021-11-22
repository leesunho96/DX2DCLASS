#pragma once
#include "Renders/Sprite.h"

class Mushroom : public Sprite
{
public:
	Mushroom(D3DXVECTOR2 position) : Sprite(Textures + L"/Mario/Mushroom.png", Shaders + L"009_Sprite.fx")
	{
		mushPosition = position;
		this->Position(position);
		this->Scale(0.1, 0.1);
	};

	virtual void Position(D3DXVECTOR2 position) { __super::Position(position); };
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	bool GetIsoverlap() { return isoverlap; };
private:
	bool isoverlap = false;
	D3DXVECTOR2 mushPosition;
};