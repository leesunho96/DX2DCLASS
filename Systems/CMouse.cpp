#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	// buttonStatus, PrefStatus, Map, Count�� �Ű������� �Էµ� 0���� �ʱ�ȭ.
	// ZeroMemory =: memset.
	// ZeroMemory : memset((Destination), 0, (Length))
	// ���� ����ü�� ���� �� ��� val = {0}���� �ص� 0���� �ʱ�ȭ.
	// {0}�� ������� ������ ��� 0���� ��� �� mov, zeromemory�� 0�� ���ÿ� push.
	// �Ϲ������� �����Ϸ��� ����ȭ �ɼ� �����ֱ� ������ �� �˾Ƽ� ����ȭ����. => ũ�� �Ű� �Ƚᵵ �ȴ�.
	 
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);
	ZeroMemory(buttonCount, sizeof(int) * 8);


	// ����Ŭ���� �Ϲ� Ŭ���� ���� ������ ���� �ð� ��. �ش� �ð����� ª�� �ԷµǸ� ���� Ŭ��, �ƴϸ� ������ Ŭ�� �ι����� �ν�
	doubleClickTime = GetDoubleClickTime();
	startDoubleClickTime[0] = GetTickCount();

	for (int i = 1; i < 8; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{

}

// �ش� �޼ҵ�� ���콺 �Է½� winproc���� ȣ��� �޼ҵ�. �ش� �޼ҵ忡�� ���� ���콺 ��ǥ, �� ������ �� ���� ����.
void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// �Էµ� �޼����� ���콺 ������ �� ��� ������ ��ǥ�� position ��ǥ ����
	if (iMessage == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	// �Էµ� �޼����� ���콺 �� ������ �� ��� �� ��ǥ �ش� ������ ����.
	if (iMessage == WM_MOUSEWHEEL)
	{
		short temp = (short)HIWORD(wParam);

		wheelPrevValue = wheelValue;
		wheelValue += (float)temp;
	}
}

void CMouse::Update()
{
	// prevStatus�� buttonStatus�� ����. ũ��� 8����Ʈ.
	// ���� ����Ǿ� �ִ� buttonStatus : ���� ȣ�⿡ �����. => prevStatus�� ���� �� ��, �ش� �� �̿�
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8);

	// buttonStatus, buttonMap�� 0���� �ʱ�ȭ. 
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	// buttonStatus[0] : ���콺 ��Ŭ���� 1, �ƴϸ� 0
	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	// buttonStatus[1] : ���콺 ��Ŭ���� 1, �ƴϸ� 0
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	// buttonStatus[2] = ���콺 �ٹ�ư Ŭ���� 1, �ƴϸ� 0
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	// ��ư�� ���� ���� ����
	for (UINT i = 0; i < 8; i++)
	{
		// prevStatus : ������ ��ư ���� : �ش� ȣ�� ������ status
		byte prevStatus = buttonPrevStatus[i];
		byte status = buttonStatus[i];

		// ���� ȣ��� �ش� ��ư �ȴ��Ȱ�, �̹� ȣ�⿡ �ش� ��ư�� ���� ���
		if (prevStatus == 0 && status == 1)
			buttonMap[i] = Button::Down;
		// ���� ȣ��� �ش� ��ư ���Ȱ�, �̹� ȣ�⿡ �ش� ��ư�� ������ ���� ���
		else if (prevStatus == 1 && status == 0)
			buttonMap[i] = Button::Up;
		// ���� ȣ��� �ش� ��ư ���Ȱ�, �̹� ȣ�⿡�� �ش� ��ư�� ���� ��� => ��� ������ �ִ� ���.
		else if (prevStatus == 1 && status == 1)
			buttonMap[i] = Button::Press;
		// �� �̿� (���� ȣ�⿡�� �ȴ��Ȱ�, �̹� ȣ�⿡�� �ȴ�������)
		else
			buttonMap[i] = Button::None;
	}

	// GetTickCount : winapi �Լ�, ���� ƽ ī��Ʈ ��ȯ
	UINT buttonStatus = GetTickCount();

	// ����Ŭ��, ���� ���� ó�� �κ�. 
	for (UINT i = 0; i < 8; i++)
	{
		// ��ư ���� ���ǽ� ��ư�� �����ִ� ���
		if (buttonMap[i] == Button::Down)
		{
			// �ش� �κ� ó�� ������ ��ư�� �̹� �ѹ� ���� ���
			if (buttonCount[i] == 1)
			{
				// ����Ŭ������ �ν��� �ð� ���Ŀ� Ŭ���� ��� => ���� Ŭ�� �ι����� �ν� �� ���
				// ��ư ī��Ʈ 0���� �ʱ�ȭ
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			// ��ư�� �������� ī��Ʈ ����
			buttonCount[i]++;

			// ���� ��ư�� �ѹ��� ���� ���(�ʱ�ȭ ���� ó������ ���� ���) �ش� �ð� ����.
			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus;
		}

		// ��ư ���� ���ǽ� ��ư�� ������ ���
		if (buttonMap[i] == Button::Up)
		{
			// ��ư�� �ѹ��� ���� ���
			if (buttonCount[i] == 1)
			{
				// ����Ŭ�� �ð��� �ʰ��� ��� �ش� ��ư ī��Ʈ �ʱ�ȭ => ���� Ŭ������ �ν�.
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			// ��ư�� �ι� ���� ��� => �ϴ� doubleclicktime ������ down-up-down������ �ݺ� �� ���. 
			// up���� doubleclicktime ������ �̷���� ��� ����Ŭ������ �ν�, up�� doubleclicktime ���Ŀ� �Ͼ ��쿡�� �߰� ó�� ���� ���� => ����Ŭ��
			else if (buttonCount[i] == 2)
			{					
				//����Ŭ������ �ν� �ϴ� ���, doubleclicktime ������ down-up-down-up �ݺ� �� ���.
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0;
			}
		}
	}

	// ���� ���콺 ��ǥ ó���� ���� �ڵ��.
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);

	// ���콺 �� �̵� ó���� ���� �ڵ�.
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


