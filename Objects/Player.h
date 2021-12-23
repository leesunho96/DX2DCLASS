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
	void SetDegree(float x);
	void SetBOnGround(bool input) { bOnGround = input; };

private:
	float moveSpeed;
	Animation* animation;
	D3DXVECTOR2 focusoffset;
	D3DXVECTOR3 lineEquation = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0, 0, 0);
	float angle = 0.0f;
	bool bToRIght = true;
	bool bOnGround = true;
	float gravity = 0.0f;
	bool activate = false;
};