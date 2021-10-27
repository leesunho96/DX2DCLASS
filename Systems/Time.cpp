#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;


// �����ڸ� private ���� => �Ϲ������� ��ü �����ϵ��� ������ �Ұ����ϴ�. static���� �����
// �޼ҵ带 ȣ���Ͽ� �ش� Ŭ������ �̿��ϴ� ���.
// �ش� ����� ���α׷� ��ü�� �ش� ��ü ���� �����ϱ� ���� �ַ� ���
// �Ϲ������δ� �̱��� �������� �̿��Ѵ�. => ��� ���α׷����� �ϳ��� ��ü�� ����, ���α׷� ��ü����
// ������ ��ü�� ����ϸ�, �ʿ����� ���� ��� ��ü ����.
// ��ü���� �޼ҵ尡 ó�� ȣ�� �Ǿ� �� ���� Ŭ���� ������ ��ü ����, ������ ��ü�� ��ȯ�Ѵ�.
// �� ��, �Ǵٽ� ��ü ���� �޼ҵ尡 ȣ�� �� ���, �̹� �����Ǿ� �ִ� ��ü�� ��ȯ�Ѵ�.
Time::Time(void) :
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0) // ���� ��� Ŭ���� ������ ���� �ʱ�ȭ.
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond); // ��ǻ�� ���κ����� Ÿ�̸Ӹ� �̿��Ͽ� �ð� ���� ����. ���� CPU�� ƽ���� tickpersecond�� ����
	fpsUpdateInterval = ticksPerSecond >> 1; // �ʴ� ƽī��Ʈ�� ���������� ����Ʈ ���� ��, fpsUpdateInterval�� ���� : 2�� ���� ȿ��.

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void)
{

}

// �ش� ��ü ��û �޼ҵ�
Time* Time::Get()
{
	assert(instance != NULL);

	return instance;
}

// �ش� ��ü ���� �޼ҵ�.
void Time::Create()
{
	assert(instance == NULL);

	instance = new Time();
}

//������ ��ü ���� �޼ҵ�
void Time::Delete()
{
	SAFE_DELETE(instance);
}


void Time::Update()
{
	if (isTimerStopped) return; // Ÿ�̸Ӱ� �����Ǿ����� �ش� �޼ҵ� ����.

	//1. ����ð��� ������ �ð� ���� �� ���� �ð��� ����Ѵ�.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime); // currentTime�� ���� CPU ƽ ��ȯ.
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond; // �ð� ��� : ���� �ð����� Ÿ�̸� ������ �ð��� �� ��, tickperSecond�� ���� : �ð� ���.
	runningTime += timeElapsed; // ���� �ð� ������ ���� ��


	//2. FPS Update
	frameCount++;// �����Ӽ� ���
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval) // ���� �ð� - ������ ������ ������Ʈ �ð� >= ������ ���� ==> ������ ���� ������ ������ �ش� �ڵ� ����, �׷��� ������
		                                                  // �׳� �Ѿ
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond; // ������ ������ �Ѿ���Ƿ� �ӽ� ���� �ð��� ����ð� / �ʴ� ƽ ��.
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond; // �ӽ� ������ ������ �ð��� ������ �����ӻ簣 / �ʴ� ƽ ��
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); // fps�� ������ī��Ʈ / (�ӽ� ���� �ð� - �ӽ� �������ð�)

		lastFPSUpdate = (INT64)currentTime; // ������ fps ������Ʈ �ð� ����.
		frameCount = 0;// ������ ī��Ʈ �ʱ�ȭ.
	}

	lastTime = currentTime; // ���� �ð� ����.
}

void Time::Print()
{

}

void Time::Start()
{
	if (!isTimerStopped) // 
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}