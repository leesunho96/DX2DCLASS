#pragma once

#include "Renders/Sprite.h"

class Boxes : public Sprite
{
public:
	Boxes() : Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		80, 112, 95, 175) 
	{};
	virtual ~Boxes() {};	
	virtual void isOverLapPlayer();
	void overlapFromUnder();


};