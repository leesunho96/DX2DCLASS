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

	virtual void SetItem() override;

	virtual Sprite* GetSprite() override { return animation->GetSprite(); };

	virtual void ApplyDamege() override;
	virtual bool GetIsValid() override { return isAvailable; };
private:
	Animation* animation;
	Sprite* ItemSprite = nullptr;
	bool isAvailable = true;
	bool isPlayingBreaking = false;
	int life = 0;
	float waitingTime = 0.0f;
	const float animationTime = 0.2f;
	const int maximumLife = 3;
	D3DXVECTOR2 Position;
	bool bIsHavingItem = false;
	bool bIsAvailableCollision = true;
};