#pragma once
#include "Character.h"

class Goliath_Arm;
class Shoulder;
class Goliath : public Character
{

public:
	Goliath(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Goliath();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void ApplyDamege(Sprite* sprite) override;
//	virtual Sprite* GetSprite() override;
	virtual D3DXVECTOR2 GetOffset() override { return D3DXVECTOR2(0, 0); };

	virtual bool IsAttackable() override;
	virtual bool IsIdle() override;
	virtual bool IsDead() override;


private:
	void UpdateArms(D3DXMATRIX& V, D3DXMATRIX& P);
	void UpdateHead(D3DXMATRIX& V, D3DXMATRIX& P);
	void UpdateBody(D3DXMATRIX& V, D3DXMATRIX& P);
	void UpdateShoulders(D3DXMATRIX& V, D3DXMATRIX& P);

public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	unsigned char PresentState;
	Animation* head;
	Sprite* body;
	Shoulder* shoulders[2];
	Goliath_Arm* goliathArms[2];
	
	vector<function<void(D3DXMATRIX& V, D3DXMATRIX& P)>> updateSprites;

	StopWatch stopwatch[2];
};