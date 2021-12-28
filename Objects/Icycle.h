#pragma once

class Player;

class Icycle
{
public:
	Icycle(int type, Player* player);
	~Icycle();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void SetPosition(D3DXVECTOR2 pos);

	void SetInvalidate();
	void SetValidate();
	

private:

	void ActWhileHole();
	void ActWhileFall();
	void ActWhileFalling();
	void ActWhileWaitFalling();

	void ResetStopWatch(float time) {
		stopwatch.ResetTimer();
		stopwatch.SetTimer(time);
	};
public:

private:
	Animation* animation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	int iPlayAnimationNum = 0;
	unsigned char StateInfo = 0;
	StopWatch stopwatch;
	Player* player;
	



	const static unsigned char Invalidate             = 0 << 0;  // 현재 비활성화
	const static unsigned char ValidateAndWaitFalling = 1 << 0;  // 활성화 되었으며, 떨어지기 대기중
	const static unsigned char ValidateAndFalling     = 1 << 1;  // 활성화 되었으며, 떨어지는중
	const static unsigned char ValidateAndFall        = 1 << 2;  // 활성화 되었으며, 떨어져 있는 상태
	const static unsigned char ValidateAndHole        = 1 << 3;  // 활성화 되었으며, 현재 사라지기전 구멍 남아있는 상태.

};