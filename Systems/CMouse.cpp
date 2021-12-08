#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	// buttonStatus, PrefStatus, Map, Count를 매개변수로 입력된 0으로 초기화.
	// ZeroMemory =: memset.
	// ZeroMemory : memset((Destination), 0, (Length))
	// 만약 구조체로 선언 된 경우 val = {0}으로 해도 0으로 초기화.
	// {0}은 어셈블리로 내려간 경우 0으로 모든 값 mov, zeromemory는 0을 스택에 push.
	// 일반적으로 컴파일러에 최적화 옵션 켜져있기 때문에 다 알아서 최적화해줌. => 크게 신경 안써도 된다.
	 
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);
	ZeroMemory(buttonCount, sizeof(int) * 8);


	// 더블클릭과 일반 클릭의 차이 구분을 위한 시간 값. 해당 시간보다 짧게 입력되면 더블 클릭, 아니면 독립된 클릭 두번으로 인식
	doubleClickTime = GetDoubleClickTime();
	startDoubleClickTime[0] = GetTickCount();

	for (int i = 1; i < 8; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{

}

// 해당 메소드는 마우스 입력시 winproc에서 호출될 메소드. 해당 메소드에서 현재 마우스 좌표, 휠 움직인 값 등을 저장.
void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// 입력된 메세지가 마우스 움직임 인 경우 움직인 좌표로 position 좌표 지정
	if (iMessage == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	// 입력된 메세지가 마우스 휠 움직임 일 경우 휠 좌표 해당 값으로 저장.
	if (iMessage == WM_MOUSEWHEEL)
	{
		short temp = (short)HIWORD(wParam);

		wheelPrevValue = wheelValue;
		wheelValue += (float)temp;
	}
}

void CMouse::Update()
{
	// prevStatus에 buttonStatus를 복사. 크기는 8바이트.
	// 현재 저장되어 있는 buttonStatus : 이전 호출에 저장됨. => prevStatus로 복사 한 후, 해당 값 이용
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8);

	// buttonStatus, buttonMap을 0으로 초기화. 
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	// buttonStatus[0] : 마우스 좌클릭시 1, 아니면 0
	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	// buttonStatus[1] : 마우스 우클릭시 1, 아니면 0
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	// buttonStatus[2] = 마우스 휠버튼 클릭시 1, 아니면 0
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	// 버튼의 현재 상태 정의
	for (UINT i = 0; i < 8; i++)
	{
		// prevStatus : 이전의 버튼 상태 : 해당 호출 이전의 status
		byte prevStatus = buttonPrevStatus[i];
		byte status = buttonStatus[i];

		// 이전 호출시 해당 버튼 안눌렸고, 이번 호출에 해당 버튼이 눌린 경우
		if (prevStatus == 0 && status == 1)
			buttonMap[i] = Button::Down;
		// 이전 호출시 해당 버튼 눌렸고, 이번 호출에 해당 버튼이 눌리지 않은 경우
		else if (prevStatus == 1 && status == 0)
			buttonMap[i] = Button::Up;
		// 이전 호출시 해당 버튼 눌렸고, 이번 호출에도 해당 버튼이 눌린 경우 => 계속 누르고 있는 경우.
		else if (prevStatus == 1 && status == 1)
			buttonMap[i] = Button::Press;
		// 그 이외 (이전 호출에도 안눌렸고, 이번 호출에도 안눌렸을때)
		else
			buttonMap[i] = Button::None;
	}

	// GetTickCount : winapi 함수, 현재 틱 카운트 반환
	UINT buttonStatus = GetTickCount();

	// 더블클릭, 관련 제어 처리 부분. 
	for (UINT i = 0; i < 8; i++)
	{
		// 버튼 상태 정의시 버튼이 눌려있는 경우
		if (buttonMap[i] == Button::Down)
		{
			// 해당 부분 처리 이전에 버튼이 이미 한번 눌린 경우
			if (buttonCount[i] == 1)
			{
				// 더블클릭으로 인식할 시간 이후에 클릭된 경우 => 단일 클릭 두번으로 인식 된 경우
				// 버튼 카운트 0으로 초기화
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			// 버튼이 눌렸으니 카운트 증가
			buttonCount[i]++;

			// 만약 버튼이 한번만 눌린 경우(초기화 이후 처음으로 눌린 경우) 해당 시간 저장.
			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus;
		}

		// 버튼 상태 정의시 버튼이 떨어진 경우
		if (buttonMap[i] == Button::Up)
		{
			// 버튼이 한번만 눌린 경우
			if (buttonCount[i] == 1)
			{
				// 더블클릭 시간이 초과된 경우 해당 버튼 카운트 초기화 => 단일 클릭으로 인식.
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			// 버튼을 두번 눌린 경우 => 일단 doubleclicktime 이전에 down-up-down까지는 반복 된 경우. 
			// up까지 doubleclicktime 이전에 이루어진 경우 더블클릭으로 인식, up이 doubleclicktime 이후에 일어난 경우에는 추가 처리 하지 않음 => 단일클릭
			else if (buttonCount[i] == 2)
			{					
				//더블클릭으로 인식 하는 경우, doubleclicktime 이전에 down-up-down-up 반복 된 경우.
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0;
			}
		}
	}

	// 현재 마우스 좌표 처리를 위한 코드들.
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);

	// 마우스 휠 이동 처리를 위한 코드.
	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;
}

D3DXVECTOR2 CMouse::GetAdjustPos(D3DXVECTOR2 camerapos)
{
	return GetAdjustPos(this->Position(), camerapos);
}

D3DXVECTOR2 CMouse::GetAdjustPos(D3DXVECTOR2 mousepos, D3DXVECTOR2 camerapos)
{
	D3DXVECTOR2 mouse = mousepos;
	D3DXVECTOR2 camera = camerapos;

	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;
	return mouse + camera;
}


