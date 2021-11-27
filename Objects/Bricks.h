#pragma once

#include "IBRICKSINTERFACE.h"

class Animation;

class Bricks : public IBRICKSINTERFACE
{
public:
	Bricks(int type, D3DXVECTOR2 position);
	virtual ~Bricks();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

private:
	Animation* animation;
	bool isAvailable = true;
	bool isPlayingBreaking = false;
	int life = 0;
	float waitingTime = 0.0f;
	const float animationTime = 0.2f;
	D3DXVECTOR2 Position;
};