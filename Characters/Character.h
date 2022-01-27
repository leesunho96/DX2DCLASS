#pragma once

#include "stdafx.h"
class Character
{
public:
		
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
	virtual void ApplyDamege(Sprite* sprite) = 0;
	// ���� idx 0 : body, ���� �浹�� ������ ����Ǵ� ��������Ʈ. �� �̿��� ��������Ʈ�� ������ ������� �ʴ�, �ݻ縸 �ϴ� ��������Ʈ��.
	virtual vector<Sprite*> GetSprite() { return sprites; };
	virtual Sprite* GetBodySprite() { return sprites[0]; };
	virtual D3DXVECTOR2 GetOffset() = 0;
	virtual bool IsAttackable() = 0;
	virtual bool IsIdle() = 0;
protected:
	vector<Sprite*> sprites;
};