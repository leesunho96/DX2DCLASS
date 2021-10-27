#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;


// 생성자를 private 설정 => 일반적으로 객체 생성하듯이 생성이 불가능하다. static으로 선언된
// 메소드를 호출하여 해당 클래스를 이용하는 방식.
// 해당 방식은 프로그램 전체의 해당 객체 수를 제한하기 위해 주로 사용
// 일반적으로는 싱글톤 패턴으로 이용한다. => 모든 프로그램에서 하나의 객체를 공유, 프로그램 전체에서
// 동일한 객체를 사용하며, 필요하지 않은 경우 객체 삭제.
// 객체생성 메소드가 처음 호출 되었 을 때는 클래스 내에서 객체 생성, 생성한 객체를 반환한다.
// 그 후, 또다시 객체 생성 메소드가 호출 된 경우, 이미 생성되어 있는 객체를 반환한다.
Time::Time(void) :
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0) // 각각 모든 클래스 내부의 변수 초기화.
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond); // 컴퓨터 메인보드의 타이머를 이용하여 시간 간격 측정. 현재 CPU의 틱을를 tickpersecond에 저장
	fpsUpdateInterval = ticksPerSecond >> 1; // 초당 틱카운트를 오른쪽으로 시프트 연산 후, fpsUpdateInterval에 대입 : 2로 나눈 효과.

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void)
{

}

// 해당 객체 요청 메소드
Time* Time::Get()
{
	assert(instance != NULL);

	return instance;
}

// 해당 객체 생성 메소드.
void Time::Create()
{
	assert(instance == NULL);

	instance = new Time();
}

//생성된 객체 삭제 메소드
void Time::Delete()
{
	SAFE_DELETE(instance);
}


void Time::Update()
{
	if (isTimerStopped) return; // 타이머가 중지되었으면 해당 메소드 종료.

	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime); // currentTime에 현재 CPU 틱 반환.
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond; // 시간 경과 : 현재 시간에서 타이머 시작한 시간을 뺀 후, tickperSecond로 나눔 : 시간 경과.
	runningTime += timeElapsed; // 실행 시간 측정을 위한 식


	//2. FPS Update
	frameCount++;// 프레임수 계산
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval) // 현재 시간 - 마지막 프레임 업데이트 시간 >= 프레임 간격 ==> 프레임 측정 간격을 넘으면 해당 코드 실행, 그렇지 않으면
		                                                  // 그냥 넘어감
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond; // 프레임 간격이 넘어갔으므로 임시 현재 시간은 현재시간 / 초당 틱 수.
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond; // 임시 마지막 프레임 시간은 마지막 프레임사간 / 초당 틱 수
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); // fps는 프레임카운트 / (임시 현재 시간 - 임시 마지막시간)

		lastFPSUpdate = (INT64)currentTime; // 마지막 fps 업데이트 시간 갱신.
		frameCount = 0;// 프레임 카운트 초기화.
	}

	lastTime = currentTime; // 현재 시간 저장.
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