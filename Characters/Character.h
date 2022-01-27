#pragma once

#include "stdafx.h"
class Character
{
public:
		
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
	virtual void ApplyDamege(Sprite* sprite) = 0;
	// 리턴 idx 0 : body, 실제 충돌시 데미지 적용되는 스프라이트. 그 이외의 스프라이트는 데미지 적용받지 않는, 반사만 하는 스프라이트들.
	virtual vector<Sprite*> GetSprite() { return sprites; };
	virtual Sprite* GetBodySprite() { return sprites[0]; };
	virtual D3DXVECTOR2 GetOffset() = 0;
	virtual bool IsAttackable() = 0;
	virtual bool IsIdle() = 0;
protected:
	vector<Sprite*> sprites;
};