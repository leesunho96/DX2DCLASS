#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{

	/*
	�� bitset 256(KEYMAX)���� �� ��Ʈ�� false�� �ʱ�ȭ�ϴ� �ڵ�, Keyboard�������̴�.
	�� ��Ʈ�� up, down�� 256��Ʈ�̸�, ���� Ű���� �Է°��� �����ϴ� ��Ʈ�̴�.
	*/
	for (int i = 0; i < KEYMAX; i++)
	{
		up.set(i, false); // up false�� �ʱ�ȭ
		down.set(i, false); // down false�� �ʱ�ȭ
	}
}

Keyboard::~Keyboard()
{
}


/*
	Down �޼ҵ�� �Է°����� �־��� key�� ���� ���� �ִ��� Ȯ���ϴ� �޼ҵ��̴�.
	GetAsynchKeyState �Լ��� ���� Ű�� ���¸� �˾ƿ��� �Լ��̸�, Ű�� �����ų�(Down), Ű�� ����������(Up) ȣ��ȴ�.
	Ű���� �Է��� ũ�� �ΰ����� ����.
	GetAsyncKeyState() : ȣ��� ���������� Key���¸� ���� -> �޼��� ť�� ��ġ�� ����.
	GetAsynchKeyState�� �Է°� Key�� ���� Ű���� ���¿� ���� ������ ���� ��ȯ��(return ���� Short)�� �ش�
	0x0000(0) : ������ ���� ���� ����, ȣ�� �������� �������� ���� ����
	0x0001(1) : ������ ���� ���� ������, ȣ�� �������� ���� ���� ���� ����
	0x8000(-128) : ������ ���� ���� ������, ȣ�� �������� ���� �ִ� ����
	0x8001(-127) : ������ �������� �ְ�, ȣ�� �������� �����ִ� ����

	GetKeyState() : �޼��� ť�� ���ļ� Key ���¸� ���� -> �޼��� ť�� Key �Է��� �����ϴ� ��� �Էµ� ���·� ó��
	return�� ó��
	=> ������Ʈ�� 1�̸� ���� �ش� Ű�� �Է� �� �����̴�.
	=> ������Ʈ�� 1�̸� Ű�� ��۵ȴ�. CAPS LOCK�� ���� Key Toggle�� ���ȴ�.
*/
bool Keyboard::Down(int key)
{
	// ���� key�� ó������ �Է� �� ��� true �� �̿ܿ��� false. & : ��Ʈ ����, �� ��Ʈ�� ���� and ������ ����. 
	if ((GetAsyncKeyState(key) & 0x8000))
	{
		// Ű�� ó������ �ԷµǾ�������, ��Ʈ�� down�� key��° ��Ʈ�� false�� ��� �ش� ��Ʈ�� true�� �����Ѵ�.(���� �ش� ��Ʈ�� ���� ������ �ǹ�)
		if (down[key] == false )
		{
			// down�� key���� ��Ʈ�� true ����
			down.set(key, true);

			// ���� key�� ���� �����̱� ������ true ��ȯ.
			return true;
		}
	}
	//GetAsyncKeyState�� 0x8000�� �ƴ� ��� (������ �ش� key�� ���� ���� �ƴϰų� ������ ��������, ȣ�� �������� �������� ���� ���)
	// �� �� �������� �ش� key�� �������� ���� ���.
	else
	{
		// down ��Ʈ���� key�� false�� ���� : key�� �������� ����.
		down.set(key, false);
	}

	// ���� key�� �������� �ʱ� ������ false ��ȯ
	return false;
}

// Down �޼ҵ忡�� ����� �۾��� up ��Ʈ�¿� �����Ŵ.
bool Keyboard::Up(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (up[key] == false)
		{
			up.set(key, true);

			return true;
		}
	}
	else
	{
		up.set(key, false);
	}

	return false;
}


// �ش� �޼ҵ�� ���� �Ű������� �־����� Key�� ���� �����̸� true �ƴϸ� false ��ȯ. 
bool Keyboard::Press(int key)
{
	if ((GetAsyncKeyState(key) & 0x8000))
		return true;

	return false;
}

// �ش� �޼ҵ�� ��ۿ� ���
// ������ �������� ���� �ȴ��������� true �ƴϸ� false
bool Keyboard::Toggle(int key)
{
	if (GetAsyncKeyState(key) & 0x0001)
		return true;

	return false;
}

void Keyboard::setIgnore()
{
	isPossible = false;
}

void Keyboard::setAccept()
{
	isPossible = true;
}
