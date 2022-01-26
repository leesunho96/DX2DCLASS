#pragma once

class StopWatch;
enum class ShoulderType
{
	Left = 0, Right
};

class Shoulder
{
public:
	Shoulder(ShoulderType shouldertype, D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Shoulder();

	Sprite* GetSprite() { return shoulder; };
	void SetDeactivate() { bIsActivate = false; };
	void SetActivate() { bIsActivate = true; };
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
private:

public:
private:
	Sprite* shoulder;
	ShoulderType shouldertype;
	D3DXVECTOR2 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 scale;
	StopWatch stopwatch;
	D3DXVECTOR2 direction;
	bool bIsActivate = false;
	//bool isforward = true;
};