#pragma once

#include "stdafx.h"
class Character
{
public:
		
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
	virtual void ApplyDamege(Sprite* sprite) = 0;
	// 리턴 idx 0 : body, 실제 충돌시 데미지 적용되는 스프라이트. 그 이외의 스프라이트는 데미지 적용받지 않는, 반사만 하는 스프라이트들.
	virtual D3DXVECTOR2 GetOffset() = 0;
	virtual bool IsAttackable() = 0;
	virtual bool IsIdle() = 0;
	virtual bool IsDead() = 0;
	virtual vector<Sprite*> GetSprite() { return sprites; };
	virtual Sprite* GetBodySprite() { return sprites[0]; };
	virtual bool IsOverlap(Sprite* sprite) { return GetBodySprite()->OBB(sprite); };
	virtual D3DXVECTOR2 GetPosition() { return GetBodySprite()->Position(); };
protected:
	// 타 클래스에서 Character 클래스를 상속받은 자식 클래스에 스프라이트를 얻으려 할 때 사용 할 스프라이트 벡터.
	// 해당 벡터는 각 클래스의 매 틱마다 업데이트 되어야 함.
	vector<Sprite*> sprites;
};