#pragma once
#include "Character.h"

class Goliath : public Character
{

public:
	Goliath(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Goliath();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void ApplyDamege(Sprite* sprite) override;
	virtual Sprite* GetSprite() override;
	virtual D3DXVECTOR2 GetOffset() override { return D3DXVECTOR2(0, 0); };

	virtual bool IsAttackable() override;
	virtual bool IsIdle() override;


private:

public:

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	Animation* head;
	Sprite* body;

	vector<Animation*> arms;

	StopWatch stopwatch[2];
};