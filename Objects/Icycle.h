#pragma once

class Icycle
{
public:
	Icycle(int type);
	~Icycle();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void SetPosition(D3DXVECTOR2 pos);

	void SetInvalidate();
	void SetValidate();

private:

public:

private:
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	bool bIsValidate = false;
	int iPlayAnimationNum = 0;
	StopWatch stopwatch;

};