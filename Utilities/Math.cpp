#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f;

// ������ ����. val1�� ������, val2�� ���� ��
float Math::Modulo(float val1, float val2)
{
	//val1�� val2���� �۾��������� val2�� ���� => ������ ����
	while (val1 - val2 >= 0)
		val1 -= val2;

	//���� �������� ��ȯ
	return val1;
}

// �������� ��ȯ. 1���� : 180��. �Է°��� �������� ��ȯ�Ͽ� float�� ��ȯ
float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}


// ������ ���� ��ȯ�Ͽ� float�� ��ȯ
float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}


// �Է°� r1, r2�� �ް�, r1�� r2 ������ float���� ��ȯ.
// �Է°��� ������ ����.
float Math::Random(float r1, float r2)
{
	srand(time(NULL));
	// random : r1�� r2������ ������ ������ ���� ������ ���ϱ�. RAND_MAX�� �������� ������ 1���� �������̴�.
	float random = ((float)rand()) / (float)RAND_MAX;
	// r2�� r1�� ���̰� ���ϱ�. ���� random�� ���Ͽ� r1 �� ���� �� ��ȯ
	float diff = r2 - r1;
	// r1�� r2�� ���̰��� rand���� ���Ͽ� ���. abs(val) < r2 - r1
	// ���� r1�� r2���� ū ��� val�� ����, �׷��� ����� ����
	float val = random * diff;
	
	// r1�� val�� ���ؼ� r1�� r2������ ���� ��ȯ.
	return r1 + val;
}


// min < val < max�̸� val�� ��ȯ, val < min�� ��� min ��ȯ, val > max �� ��� max ��ȯ�Ѵ�.
float Math::Clamp(float value, float min, float max)
{
	// value�� max���� ũ�� val = max, �ƴϸ� val = val
	value = value > max ? max : value;
	// value�� min���� ������ val = min, �ƴϸ� val = val
	value = value < min ? min : value;

	// ���� ���ϴ� ����� ��ȯ.
	return value;
}

// ���� Random�� �����ε� ����. int���� �Է�/��ȯ ������ ���´�.
int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}