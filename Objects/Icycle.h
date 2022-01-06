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
	bool GetValidate() { return StateInfo == Invalidate ? true : false; };
	

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
	Player* player;
	Gravity gravity;
	StopWatch stopwatch;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 speed   = D3DXVECTOR2(0.0f, 200.0f);
	int iPlayAnimationNum = 0;
	



	const static unsigned char Invalidate             = 0 << 0;  // ���� ��Ȱ��ȭ
	const static unsigned char ValidateAndWaitFalling = 1 << 0;  // Ȱ��ȭ �Ǿ�����, �������� �����
	const static unsigned char ValidateAndFalling     = 1 << 1;  // Ȱ��ȭ �Ǿ�����, ����������
	const static unsigned char ValidateAndFall        = 1 << 2;  // Ȱ��ȭ �Ǿ�����, ������ �ִ� ����
	const static unsigned char ValidateAndHole        = 1 << 3;  // Ȱ��ȭ �Ǿ�����, ���� ��������� ���� �����ִ� ����.

	unsigned char StateInfo = Invalidate;
};