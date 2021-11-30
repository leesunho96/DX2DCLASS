#pragma once
#include "stdafx.h"

class IBRICKSINTERFACE
{
public:
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
	virtual void SetItem() = 0;
private:
};