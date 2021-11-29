#pragma once
#include "IBRICKSINTERFACE.h"

class NonBreakableBricks :
	public IBRICKSINTERFACE
{
public:
	NonBreakableBricks(D3DXVECTOR2 position);
	virtual ~NonBreakableBricks();
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
private:
	Animation* animation;
	D3DXVECTOR2 Position;

};

