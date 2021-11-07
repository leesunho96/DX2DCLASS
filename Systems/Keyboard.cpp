#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{

	/*
	총 bitset 256(KEYMAX)개의 각 비트를 false로 초기화하는 코드, Keyboard생성자이다.
	각 비트셋 up, down은 256비트이며, 각각 키보드 입력값에 대응하는 비트이다.
	*/
	for (int i = 0; i < KEYMAX; i++)
	{
		up.set(i, false); // up false로 초기화
		down.set(i, false); // down false로 초기화
	}
}

Keyboard::~Keyboard()
{
}


/*
	Down 메소드는 입력값으로 주어진 key가 현재 눌려 있는지 확인하는 메소드이다.
	GetAsynchKeyState 함수는 현재 키의 상태를 알아오는 함수이며, 키가 눌리거나(Down), 키가 떨어졌을떄(Up) 호출된다.
	키보드 입력은 크게 두가지가 존재.
	GetAsyncKeyState() : 호출된 시점에서의 Key상태를 조사 -> 메세지 큐를 거치지 않음.
	GetAsynchKeyState는 입력값 Key에 대한 키보드 상태에 대해 다음과 같은 반환값(return 값은 Short)을 준다
	0x0000(0) : 이전에 누른 적이 없고, 호출 시점에도 눌려있지 않은 상태
	0x0001(1) : 이전에 누른 적이 있지만, 호출 시점에서 눌려 있지 않은 상태
	0x8000(-128) : 이전에 누른 적이 없지만, 호출 시점에는 눌려 있는 상태
	0x8001(-127) : 이전에 누른적이 있고, 호출 시점에도 눌려있는 상태

	GetKeyState() : 메세지 큐를 거쳐서 Key 상태를 조사 -> 메세지 큐에 Key 입력이 존재하는 경우 입력된 상태로 처리
	return값 처리
	=> 상위비트가 1이면 현재 해당 키는 입력 된 상태이다.
	=> 하위비트가 1이면 키가 토글된다. CAPS LOCK과 같은 Key Toggle에 사용된다.
*/
bool Keyboard::Down(int key)
{
	// 만약 key가 처음으로 입력 된 경우 true 그 이외에는 false. & : 비트 연산, 각 비트에 대한 and 연산을 수행. 
	if ((GetAsyncKeyState(key) & 0x8000))
	{
		// 키가 처음으로 입력되어있으며, 비트셋 down의 key번째 비트가 false인 경우 해당 비트를 true로 설정한다.(현재 해당 비트가 눌려 있음을 의미)
		if (down[key] == false )
		{
			// down의 key번쨰 비트를 true 세팅
			down.set(key, true);

			// 현재 key가 눌린 상태이기 떄문에 true 반환.
			return true;
		}
	}
	//GetAsyncKeyState가 0x8000이 아닌 경우 (이전에 해당 key를 누른 것이 아니거나 이전에 눌렀으며, 호출 시점에도 눌려있지 않은 경우)
	// 즉 현 시점에서 해당 key가 눌려있지 않은 경우.
	else
	{
		// down 비트셋의 key를 false로 세팅 : key가 눌려있지 않음.
		down.set(key, false);
	}

	// 현재 key가 눌려있지 않기 때문에 false 반환
	return false;
}

// Down 메소드에서 진행된 작업을 up 비트셋에 적용시킴.
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


// 해당 메소드는 현재 매개변수로 주어지는 Key가 눌린 상태이면 true 아니면 false 반환. 
bool Keyboard::Press(int key)
{
	if ((GetAsyncKeyState(key) & 0x8000))
		return true;

	return false;
}

// 해당 메소드는 토글에 사용
// 이전에 눌렸으나 현재 안눌려있으면 true 아니면 false
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
