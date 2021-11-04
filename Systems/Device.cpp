#include "stdafx.h"
#include "Device.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitWindow(hInstance, nShowCmd);
	InitDirect3D(hInstance);

	Running();

	Destroy();

	return 0;
}


HWND Hwnd = NULL;
wstring Title = L"Draw Sprite";

IDXGISwapChain* SwapChain;
ID3D11Device* Device;
ID3D11DeviceContext* DeviceContext;
ID3D11RenderTargetView* RTV;
int world[10][15];

/*
		
*/

Keyboard* Key;
Time* Timer;

void InitWindow(HINSTANCE hInstance, int ShowWnd)
{
	//Register Class
	{
		// 윈도우 클래스 확장 구조체
		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);//해당 구조체 크기
		wndClass.style = CS_HREDRAW | CS_VREDRAW; // 수평으로 그리기 | 수직으로 그리기
		wndClass.lpfnWndProc = WndProc; 
		wndClass.cbClsExtra = NULL; // 추가기능, 사용 안함
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = hInstance; // 현재 창의 프로그램 식별자
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = Title.c_str();
		wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // extra의 기능.

		WORD check = RegisterClassEx(&wndClass);
		assert(check != 0);
	}

	//Create Handle
	{
		Hwnd = CreateWindowEx
		(
			NULL, 
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			Width, Height,
			NULL,
			NULL,
			hInstance,
			NULL
		);
		assert(Hwnd != NULL); // 조건이 true 이면 통과, 아니면 중단점걸고 에러 출력.
	}

	// 사각형 구조체
	RECT rect = { 0, 0, (LONG)Width, (LONG)Height };
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		Hwnd,
		centerX,
		centerY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		TRUE
	);

	ShowWindow(Hwnd, ShowWnd);
	UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance)
{
	//Create Device and DeviceContext, SwapChain
	{
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = Width;
		bufferDesc.Height = Height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferDesc = bufferDesc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = Hwnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &desc, &SwapChain, &Device, NULL, &DeviceContext
		);
		assert(SUCCEEDED(hr));
	}

	//Create BackBuffer
	{
		HRESULT hr;

		ID3D11Texture2D* BackBuffer;
		hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(hr));

		hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RTV);
		assert(SUCCEEDED(hr));
		BackBuffer->Release();

		DeviceContext->OMSetRenderTargets(1, &RTV, NULL);
	}



	//Create Viewport
	{
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = Width;
		viewport.Height = Height;

		DeviceContext->RSSetViewports(1, &viewport);
	}
}

void Destroy()
{
	SwapChain->Release();
	Device->Release();
	DeviceContext->Release();
	RTV->Release();
}

WPARAM Running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	ImGui::Create(Hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();

	Key = new Keyboard;
	Timer = new Time();
	InitScene();
	while (true)
	{
		// peekMessage : 메세지큐에 값이 없어도 반환
		// getmessage : 메세지큐에 값이 올 때까지 대기
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			// msg 변수에 키보드 메세지가 들어 있는 경우 키에 대응하는 문자 생성.
			// 메세지가 WM_KEYDOWN인지, 눌러진 키가 문자 키 인지 확인 후, 맞는경우 WM_CHAR 메세지 생성해서 msg 에 덧붙임.
			TranslateMessage(&msg);
			// 메세지를 WndProc에 보냄.
			DispatchMessage(&msg);
		}
		else 
		{
			Timer->Update();
			Update();

			ImGui::Update();

			Render();
		}
	}
	DestroyScene();

	delete(Key);
	delete(Timer);
	ImGui::Delete();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// 실제 마우스 좌표보다 화면 베젤로 인해서 약간 틀어짐.
	if(ImGui::WndProc((UINT*)hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) 
			{
				DestroyWindow(hwnd);
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


