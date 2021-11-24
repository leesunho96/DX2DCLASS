#pragma once

class DirectWrite
{
public:
	static void Create();
	static void Delete();

	// ������ ��ü ȣ���ϴ� static �޼ҵ�
	static DirectWrite* Get();
	//  ������ devicecontext�� ȣ���ϴ� static �޼ҵ�
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	// backbuffer ����. ȭ���� ũ�Ⱑ �ٲ�� ��� ���� backbuffer�� 
	// �ٲ� backbuffer�� ũ�� ���̰� �߻� �ϱ� ������ ���� backbuffer ������ �ʿ䰡 �ִ�.
	// �ش� �޼ҵ�� ó�� ���α׷� �����, ȭ�� â ũ�Ⱑ �ٲ� �� ��쿡 ȣ��ȴ�.
	static void CreateBackBuffer();
	// ������ �����Ǿ� �ִ� Backbuffer�� ��ȯ�ϴ� �޼ҵ�.
	// DirectWrite Ŭ������ ����� Backbuffer�� �ü���� ��ȯ�Ѵ�.
	// �ش� �޼ҵ�� ���α׷��� ����� ��, ȭ�� â ũ�Ⱑ ���� �� �� �ι� ȣ��ȴ�.
	static void DeleteBackBuffer();

	// ���� �ؽ�Ʈ�� ��� �� �� ����ϴ� �޼ҵ��̴�.
	static void RenderText(wstring& text, RECT& rect);

private:
	// �ش� Ŭ������ �̱��� ���� �̿�� ��� �� ���� ��ü ������ ���� ������
	static DirectWrite* instance;

private:
	// ������/�Ҹ���, �̱��� �����̶� private ������ �̿�
	DirectWrite();
	~DirectWrite();

private:
	// direct2D ���ҽ� ����� ������
	ID2D1Factory1* factory;
	static IDWriteFactory* writeFactory;

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap;
	static IDXGISurface* surface;


	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;
};