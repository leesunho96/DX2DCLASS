#pragma once

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	void SetTimer(float input) { max_Time = input; };
	void ResetTimer() { max_Time = 0.0f; present_Time = 0.0f; isOver = false; };

	void Update();
	bool IsOver();
private:
	float max_Time = 0.0f;
	float present_Time = 0.0f;
	bool isOver = false;
};