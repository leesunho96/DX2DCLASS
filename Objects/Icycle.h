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
	



	const static unsigned char Invalidate             = 0 << 0;  // ���� ��Ȱ��ȭ
	const static unsigned char ValidateAndWaitFalling = 1 << 0;  // Ȱ��ȭ �Ǿ�����, �������� �����
	const static unsigned char ValidateAndFalling     = 1 << 1;  // Ȱ��ȭ �Ǿ�����, ����������
	const static unsigned char ValidateAndFall        = 1 << 2;  // Ȱ��ȭ �Ǿ�����, ������ �ִ� ����
	const static unsigned char ValidateAndHole        = 1 << 3;  // Ȱ��ȭ �Ǿ�����, ���� ��������� ���� �����ִ� ����.

};