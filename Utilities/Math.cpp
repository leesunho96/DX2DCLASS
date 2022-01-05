#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f;

// 나머지 연산. val1이 원본값, val2가 나눌 값
float Math::Modulo(float val1, float val2)
{
	//val1이 val2보다 작아질때까지 val2를 뺀다 => 나머지 연산
	while (val1 - val2 >= 0)
		val1 -= val2;

	//구한 나머지를 반환
	return val1;
}

// 라디안으로 변환. 1라디안 : 180도. 입력값을 라디안으로 변환하여 float로 반환
float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}


// 라디안을 도로 변환하여 float로 반환
float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}


// 입력값 r1, r2를 받고, r1과 r2 사이의 float값을 반환.
// 입력값에 순서는 없다.
float Math::Random(float r1, float r2)
{
	srand(time(NULL));
	// random : r1과 r2사이의 랜덤값 생성을 위해 랜덤값 구하기. RAND_MAX로 나누었기 때문에 1보다 작을것이다.
	float random = ((float)rand()) / (float)RAND_MAX;
	// r2와 r1의 차이값 구하기. 추후 random과 곱하여 r1 과 더한 후 반환
	float diff = r2 - r1;
	// r1과 r2의 차이값에 rand값을 곱하여 계산. abs(val) < r2 - r1
	// 만약 r1이 r2보다 큰 경우 val은 음수, 그래도 결과는 동일
	float val = random * diff;
	
	// r1과 val을 더해서 r1과 r2사이의 값을 반환.
	return r1 + val;
}


// min < val < max이면 val을 반환, val < min인 경우 min 반환, val > max 인 경우 max 반환한다.
float Math::Clamp(float value, float min, float max)
{
	// value가 max보다 크면 val = max, 아니면 val = val
	value = value > max ? max : value;
	// value가 min보다 작으면 val = min, 아니면 val = val
	value = value < min ? min : value;

	// 따라서 원하는 결과값 반환.
	return value;
}

// 위의 Random의 오버로딩 버전. int형을 입력/반환 값으로 갖는다.
int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}