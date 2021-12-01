#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	
	Sprite* GetSprite() { return animation->GetSprite(); };
	
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void GetItem(int type);

private:
	void GetBullet() { bIsGetBulletItem = true; };
	void GetLargerItem() { bIsGetLargerItem = true; };
	void GetMoreBallItem() { bIsGetMoreBall = true; };
private:
	float moveSpeed;
	Animation* animation;
	D3DXVECTOR2 focusoffset;
	int clipNum = 0;
	bool bIsGetLargerItem = false;
	bool bIsGetBulletItem = false;
	bool bIsGetMoreBall = false;
	float bulletCooltime = 0.0f;
};