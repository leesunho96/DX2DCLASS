#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void StartJump();
	RECT GetWorldLocation() { return animation->GetWorldLocation(); };
	void GetMushroom();
	void ApplyDamege();
	void LoseLife() { lives--; animation->SetScale(1.0f, 1.0f);};
	void StageClear() { isPlayingGame = false; };
	void SetVelocity() { velocity = 0.2; };
	
private:
	float moveSpeed;
	float moveXPos = 0.0f;
	D3DXVECTOR2 focusoffset;
	float velocity = 0.0f;
	float gravity = -0.001f;
	float fBottomY = 50.0f;
	bool bOnGround = false;
	bool bIsJumpable = false;
	D3DXVECTOR2 position;
	Animation* animation;
	vector<Sprite*> heart;
	int lives = 3;
	bool isPlayingGame = true;
	void CharacterRestart() { position = D3DXVECTOR2(-4000, 200); animation->SetPosition(position); };
	bool isInvincible = false;
private:
	void KeyInput(D3DXVECTOR2& position, bool& bMove);
	void CheckPosition(D3DXVECTOR2& position);
	void EndJump();
	//bool isOverlapBox();
	//bool isOverBox(float fPositonY);
	//bool isUnderBox(float fPositionY);
};