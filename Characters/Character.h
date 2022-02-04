#pragma once

#include "stdafx.h"
class Character
{
public:
		
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
	virtual void ApplyDamege(Sprite* sprite) = 0;
	// ���� idx 0 : body, ���� �浹�� ������ ����Ǵ� ��������Ʈ. �� �̿��� ��������Ʈ�� ������ ������� �ʴ�, �ݻ縸 �ϴ� ��������Ʈ��.
	virtual D3DXVECTOR2 GetOffset() = 0;
	virtual bool IsAttackable() = 0;
	virtual bool IsIdle() = 0;
	virtual bool IsDead() = 0;
	virtual vector<Sprite*> GetSprite() { return sprites; };
	virtual Sprite* GetBodySprite() { return sprites[0]; };
	virtual bool IsOverlap(Sprite* sprite) { return GetBodySprite()->OBB(sprite); };
	virtual D3DXVECTOR2 GetPosition() { return GetBodySprite()->Position(); };
protected:
	// Ÿ Ŭ�������� Character Ŭ������ ��ӹ��� �ڽ� Ŭ������ ��������Ʈ�� ������ �� �� ��� �� ��������Ʈ ����.
	// �ش� ���ʹ� �� Ŭ������ �� ƽ���� ������Ʈ �Ǿ�� ��.
	vector<Sprite*> sprites;
};