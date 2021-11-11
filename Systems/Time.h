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
	static bool isTimerStopped;///< 타이머 중지
	static float timeElapsed;///< 이전 프레임으로부터 경과시간
};

#pragma once

