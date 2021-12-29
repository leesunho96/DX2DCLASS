#pragma once

class Gravity
{
public:
	Gravity();	
	~Gravity();

	void ResetValues();
	void SetGravityAndVelcotiy(D3DXVECTOR2 gravity, D3DXVECTOR2 velocity);
	void SetGravity(D3DXVECTOR2 gravityValue);
	void SetVelocity(D3DXVECTOR2 velocity);
	void SetValid() { bIsValid = true; };
	void SetInvalid() { bIsValid = false; };
	bool GetIsValid() { return bIsValid; };
	float GetVelocity() { return velocity.y; };
	void Update();
	D3DXVECTOR2 GetAdjustPosition(D3DXVECTOR2 position);

private:

public:

private:
	D3DXVECTOR2 gravityValue;
	D3DXVECTOR2 velocity;
	bool bIsValid = false;
};

