#include "stdafx.h"
#include "DirectWrite.h"

// static 변수들 초기화.
DirectWrite* DirectWrite::instance = NULL;

IDWriteFactory* DirectWrite::writeFactory = NULL;
ID2D1DeviceContext* DirectWrite::deviceContext = NULL;
ID2D1Bitmap1* DirectWrite::bitmap = NULL;
IDXGISurface* DirectWrite::surface = NULL;

ID2D1SolidColorBrush* DirectWrite::brush = NULL;
IDWriteTextFormat* DirectWrite::format = NULL;

// 객체 생성 메소드. 일반적으로 프로그램 실행시 초기화 할 떄 호출 될 것. 이미 호출 된 경우 재호출을 방지 하기 위해 assert 로 체크
void DirectWrite::Create()
{
	assert(instance == NULL);

	instance = new DirectWrite();
}

// 객체 삭제 메소드. 혹시나 여러번 호출 된 경우를 방지 하기 위하여 Safe_Delete
void DirectWrite::Delete()
{
	SAFE_DELETE(instance);
}

// 객체 사용시 해당 객체를 받기 위한 Get 메소드
DirectWrite* DirectWrite::Get()
{
	return instance;
}

// 생성자
DirectWrite::DirectWrite()
{
	HRESULT hr;
	// DWriteCreateFactory

	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED, // 해당 메소드로 생성할 factory가 공유 객체인지 독립된 객체인지 설정을 위한 변수, Shared : 0, Isolated : 1
		__uuidof(IDWriteFactory),   // directWrite factory interface를 구분하기 위한 GUID 값.
		(IUnknown **)&writeFactory // writeFactory에 생성된 factory를 저장
	);
	assert(SUCCEEDED(hr));

	// D2D1_FACTORY_OPTIONS {
	//	D2D1_DEBUG_LEVEL; // DebugLevel 결정
	//  }
	//  DEBUG LEVEL : 
	//	D2D1_DEBUG_LEVEL_NONE = 0,					: 디버그 결과물 생성 X
	//	D2D1_DEBUG_LEVEL_ERROR = 1,					: 디버그시 에러메세지 출력 
	//	D2D1_DEBUG_LEVEL_WARNING = 2,				: 디버그시 디버그 계층에 경고 메세지 출력
	//	D2D1_DEBUG_LEVEL_INFORMATION = 3,			: 디버그시 디버그 계층에 성능 향상을 위한 분석 정보, 경고, 에러 메세지를 제공.
	//	D2D1_DEBUG_LEVEL_FORCE_DWORD = 0xffffffff	
	//  디버그 계층(Debug Layer) : SwapChain 생성시 (d3d11CreateDevice / d3d11CreateDeviceAndSwapChain) d3d11_create_device_debug flag 설정해줘야함.

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING; 

	// D2D1CreateFactory(
	//		D2d1_FACTORY_TYPE,				: factory type, in 매개 변수
	//		REFIID,							: riid(IID *), in  매개 변수
	//		const D2D1_FACTORY_OPTIONS,		: factory_options, in/optional 매개 변수
	//		void							: **ppIFactory, out 매개변수
	//) : direct2d 자원 생성에 사용되는 메소드

	// D2D1_FACTORY_TYPE :
	//D2D1_FACTORY_TYPE_SINGLE_THREADED = 0,
	//	D2D1_FACTORY_TYPE_MULTI_THREADED = 1,
	//	D2D1_FACTORY_TYPE_FORCE_DWORD = 0xffffffff

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	assert(SUCCEEDED(hr));

	// IDXGIDevice : DXGI 이미지 객체 상속을 위한 인터페이스.
	IDXGIDevice* dxgiDevice;
	
	// dxgiDevic에 Device의 QueryInterface 저장.
	hr = Device->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	// dxgoDevice를 입력값으로 받아서 device에 id2d1device 생성
	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	// device에 deviceContext 생성
	hr = device->CreateDeviceContext
	(
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

DirectWrite::~DirectWrite()
{
	DeleteBackBuffer();
}

// backbuffer 생성 메소드
void DirectWrite::CreateBackBuffer()
{
	HRESULT hr;
	// 기존에 생성되어있는 swapchain에서 buffer 가져옴.
	// GetBuffer(
	//		UINT		: Buffer,
	//		REFIID		: riid
	//		void**		: ppSurface
	//)
	hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void **)&surface);
	assert(SUCCEEDED(hr));

	// D2D1_BITMAP_PROPERTIES1
	// {
//			D2D1_PIXEL_FORMAT pixelFormat;
//			FLOAT dpiX;
//			FLOAT dpiY;

//			D2D1_BITMAP_OPTIONS bitmapOptions;
//			_Field_size_opt_(1) ID2D1ColorContext *colorContext;
//		}
	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = NULL;

	// surface를 입력받은 후 bp에 정의된 속성대로 비트맵 생성 후, bitmap에 저장.
	hr = deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap);
	assert(SUCCEEDED(hr));

	// 주어진 이미지(bitmap)을 target으로 설정
	deviceContext->SetTarget(bitmap);

	// brush 설정.
	hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush);
	assert(SUCCEEDED(hr));

	// textformat 생성
	writeFactory->CreateTextFormat
	(
		L"돋움체", NULL
		, DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL
		, 15, L"ko", &format
	);
}

void DirectWrite::DeleteBackBuffer()
{
	deviceContext->SetTarget(NULL);

	SAFE_RELEASE(brush);
	SAFE_RELEASE(format);

	SAFE_RELEASE(bitmap);
	SAFE_RELEASE(surface);
}

void DirectWrite::RenderText(wstring & text, RECT & rect)
{
	D2D1_RECT_F temp;
	temp.left = (float)rect.left;
	temp.top = (float)rect.top;
	temp.right = (float)rect.right;
	temp.bottom = (float)rect.bottom;

	DirectWrite::GetDC()->DrawTextW(text.c_str(), text.size(), format, &temp, brush);
}