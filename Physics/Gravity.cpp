#include "stdafx.h"
#include "Gravity.h"

Gravity::Gravity()
{
}

Gravity::~Gravity()
{

}

void Gravity::ResetValues()
{	
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

void Gravity::SetGravityAndVelcotiy(D3DXVECTOR2 gravity, D3DXVECTOR2 velocity)
{
	SetGravity(gravity);
	SetVelocity(velocity);
}

void Gravity::SetGravity(D3DXVECTOR2 gravityValue)
{
	this->gravityValue = gravityValue;
}

void Gravity::SetVelocity(D3DXVECTOR2 velocity)
{
	this->velocity = velocity;
}

void Gravity::Update()
{
	if (!bIsValid)
	{
		return;
	}
	velocity += gravityValue * Timer->Elapsed();
}

D3DXVECTOR2 Gravity::GetAdjustPosition(D3DXVECTOR2 position)
{
	return position + (velocity * Timer->Elapsed());
}
