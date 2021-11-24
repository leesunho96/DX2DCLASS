#pragma once

class DirectWrite
{
public:
	static void Create();
	static void Delete();

	// 생성된 객체 호출하는 static 메소드
	static DirectWrite* Get();
	//  생성된 devicecontext를 호출하는 static 메소드
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	// backbuffer 생성. 화면의 크기가 바뀌는 경우 기존 backbuffer와 
	// 바뀐 backbuffer의 크기 차이가 발생 하기 때문에 새로 backbuffer 생성할 필요가 있다.
	// 해당 메소드는 처음 프로그램 실행시, 화면 창 크기가 바뀔때 두 경우에 호출된다.
	static void CreateBackBuffer();
	// 기존에 생성되어 있는 Backbuffer를 반환하는 메소드.
	// DirectWrite 클래스가 사용할 Backbuffer를 운영체제에 반환한다.
	// 해당 메소드는 프로그램이 종료될 때, 화면 창 크기가 변경 될 때 두번 호출된다.
	static void DeleteBackBuffer();

	// 실제 텍스트를 출력 할 때 사용하는 메소드이다.
	static void RenderText(wstring& text, RECT& rect);

private:
	// 해당 클래스의 싱글톤 패턴 이용시 사용 될 공용 객체 저장을 위한 포인터
	static DirectWrite* instance;

private:
	// 생성자/소멸자, 싱글톤 패턴이라 private 생성자 이용
	DirectWrite();
	~DirectWrite();

private:
	// direct2D 리소스 저장용 포인터
	ID2D1Factory1* factory;
	static IDWriteFactory* writeFactory;

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap;
	static IDXGISurface* surface;


	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;
};