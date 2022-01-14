#include "stdafx.h"
#include "DirectWrite.h"

// static ������ �ʱ�ȭ.
DirectWrite* DirectWrite::instance = NULL;

IDWriteFactory* DirectWrite::writeFactory = NULL;
ID2D1DeviceContext* DirectWrite::deviceContext = NULL;
ID2D1Bitmap1* DirectWrite::bitmap = NULL;
IDXGISurface* DirectWrite::surface = NULL;

ID2D1SolidColorBrush* DirectWrite::brush = NULL;
IDWriteTextFormat* DirectWrite::format = NULL;

// ��ü ���� �޼ҵ�. �Ϲ������� ���α׷� ����� �ʱ�ȭ �� �� ȣ�� �� ��. �̹� ȣ�� �� ��� ��ȣ���� ���� �ϱ� ���� assert �� üũ
void DirectWrite::Create()
{
	assert(instance == NULL);

	instance = new DirectWrite();
}

// ��ü ���� �޼ҵ�. Ȥ�ó� ������ ȣ�� �� ��츦 ���� �ϱ� ���Ͽ� Safe_Delete
void DirectWrite::Delete()
{
	SAFE_DELETE(instance);
}

// ��ü ���� �ش� ��ü�� �ޱ� ���� Get �޼ҵ�
DirectWrite* DirectWrite::Get()
{
	return instance;
}

// ������
DirectWrite::DirectWrite()
{
	HRESULT hr;
	// DWriteCreateFactory

	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED, // �ش� �޼ҵ�� ������ factory�� ���� ��ü���� ������ ��ü���� ������ ���� ����, Shared : 0, Isolated : 1
		__uuidof(IDWriteFactory),   // directWrite factory interface�� �����ϱ� ���� GUID ��.
		(IUnknown **)&writeFactory // writeFactory�� ������ factory�� ����
	);
	assert(SUCCEEDED(hr));

	// D2D1_FACTORY_OPTIONS {
	//	D2D1_DEBUG_LEVEL; // DebugLevel ����
	//  }
	//  DEBUG LEVEL : 
	//	D2D1_DEBUG_LEVEL_NONE = 0,					: ����� ����� ���� X
	//	D2D1_DEBUG_LEVEL_ERROR = 1,					: ����׽� �����޼��� ��� 
	//	D2D1_DEBUG_LEVEL_WARNING = 2,				: ����׽� ����� ������ ��� �޼��� ���
	//	D2D1_DEBUG_LEVEL_INFORMATION = 3,			: ����׽� ����� ������ ���� ����� ���� �м� ����, ���, ���� �޼����� ����.
	//	D2D1_DEBUG_LEVEL_FORCE_DWORD = 0xffffffff	
	//  ����� ����(Debug Layer) : SwapChain ������ (d3d11CreateDevice / d3d11CreateDeviceAndSwapChain) d3d11_create_device_debug flag �����������.

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING; 

	// D2D1CreateFactory(
	//		D2d1_FACTORY_TYPE,				: factory type, in �Ű� ����
	//		REFIID,							: riid(IID *), in  �Ű� ����
	//		const D2D1_FACTORY_OPTIONS,		: factory_options, in/optional �Ű� ����
	//		void							: **ppIFactory, out �Ű�����
	//) : direct2d �ڿ� ������ ���Ǵ� �޼ҵ�

	// D2D1_FACTORY_TYPE :
	//D2D1_FACTORY_TYPE_SINGLE_THREADED = 0,
	//	D2D1_FACTORY_TYPE_MULTI_THREADED = 1,
	//	D2D1_FACTORY_TYPE_FORCE_DWORD = 0xffffffff

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	assert(SUCCEEDED(hr));

	// IDXGIDevice : DXGI �̹��� ��ü ����� ���� �������̽�.
	IDXGIDevice* dxgiDevice;
	
	// dxgiDevic�� Device�� QueryInterface ����.
	hr = Device->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	// dxgoDevice�� �Է°����� �޾Ƽ� device�� id2d1device ����
	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	// device�� deviceContext ����
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

// backbuffer ���� �޼ҵ�
void DirectWrite::CreateBackBuffer()
{
	HRESULT hr;
	// ������ �����Ǿ��ִ� swapchain���� buffer ������.
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

	// surface�� �Է¹��� �� bp�� ���ǵ� �Ӽ���� ��Ʈ�� ���� ��, bitmap�� ����.
	hr = deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap);
	assert(SUCCEEDED(hr));

	// �־��� �̹���(bitmap)�� target���� ����
	deviceContext->SetTarget(bitmap);

	// brush ����.
	hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush);
	assert(SUCCEEDED(hr));

	// textformat ����
	writeFactory->CreateTextFormat
	(
		L"����ü", NULL
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