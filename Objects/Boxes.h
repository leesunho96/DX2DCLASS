#pragma once

#include "Renders/Sprite.h"
class Mushroom;


class Boxes : public Sprite
{
public:
	Boxes() : Sprite(Textures + L"/Mario/Brick.png", Shaders + L"009_Sprite.fx",
		80, 112, 95, 127) 
	{};
	virtual ~Boxes() {};	
	virtual void isOverLapPlayer();
	
	void overlapFromUnder();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	
private:
	Mushroom* mushroom = nullptr;
	bool isAvailable = true;
	vector<Mushroom*> temp;
};