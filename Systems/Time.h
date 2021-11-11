#pragma once

class Time
{
public:
	Time();
	~Time();

	void Update();

	float Running();
	float Elapsed();
	static float Delta() { return isTimerStopped ? 0.0f : timeElapsed; };
private:
	__int64 tick;
	__int64 start;

	__int64 elapsed;
	__int64 last;
	static bool isTimerStopped;///< Ÿ�̸� ����
	static float timeElapsed;///< ���� ���������κ��� ����ð�
};

#pragma once

