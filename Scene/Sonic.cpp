#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"


Sonic::Sonic(SceneValues * values) : Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
}

Sonic::~Sonic()
{
	for (Marker* marker : markers)
	{
		SAFE_DELETE(marker);
	}
	SAFE_DELETE(backGround);
}

D3DXVECTOR2 mpos;

void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	D3DXVECTOR2 mouse = Mouse->Position();
	
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;
	D3DXVECTOR2 camera = values->MainCamera->GetPosition();
	mpos = mouse + camera;

	if (Mouse->Down(0) == true)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mpos));
	}

	for (Marker* marker : markers)
	{
		marker->Update(V, P);
	}
}

void Sonic::Render()
{	
	//Binary

	if (ImGui::Button("Save Binary"))
	{
		function<void(wstring)> f = bind(&Sonic::SaveComplete, this, placeholders::_1);

		// L"" : 초기 디폴트 저장 파일 이름
		// L"Binary===" : 필터 이름
		// 
		Path::SaveFileDialog(L"SaveFile", L"Binary\0*.bin",L".", f, Hwnd);
	}

	if (ImGui::Button("Load Binary"))
	{
		function<void(wstring)> f = bind(&Sonic::OpenComplete, this, placeholders::_1);

		// L"" : 초기 디폴트 저장 파일 이름
		// L"Binary===" : 필터 이름
		// 
		Path::SaveFileDialog(L"SaveFile", L"Binary\0*.bin", L".", f, Hwnd);
	}

	if (ImGui::Button("Delete Save FILE"))
	{
		function<void(wstring)> f = bind(&Sonic::DeleteComplete, this, placeholders::_1);

		// L"" : 초기 디폴트 저장 파일 이름
		// L"Binary===" : 필터 이름
		// 
		Path::SaveFileDialog(L"SaveFile", L"Binary\0*.bin", L".", f, Hwnd);
	}

	backGround->Render();
	
	for (Marker* marker : markers)
	{
		marker->Render();
	}

	ImGui::LabelText("MousePosition", "%.0f , %.0f", mpos.x, mpos.y);
}

void Sonic::SaveComplete(wstring name)
{
	BinaryWriter* w = new BinaryWriter();
	w->Open(name);

	vector<D3DXVECTOR2> v(markers.size());
	for (auto marker : markers)
	{
		v.push_back(marker->Position());
	}

	w->UInt(v.size());
	w->Byte(&v[0], sizeof(D3DXVECTOR2) * v.size());
	w->Close();
	SAFE_DELETE(w);

}

void Sonic::OpenComplete(wstring name)
{

	for (auto a : markers)
	{
		SAFE_DELETE(a);
	}
	markers.clear();

	BinaryReader* r = new BinaryReader();
	r->Open(name);

	UINT count = r->UInt();

	vector<D3DXVECTOR2> v;
	v.assign(count, D3DXVECTOR2());

	void* ptr = (void*)&(v[0]);
	r->Byte(&ptr, sizeof(D3DXVECTOR2) * count);


	for (UINT i = 0; i < count; i++)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", v[i]));
	}

	r->Close();


}

void Sonic::DeleteComplete(wstring name)
{
	for (auto a : markers)
	{
		SAFE_DELETE(a);
	}
	markers.clear();
	if (Path::ExistFile(name))
	{
		//remove("marker.bin");
		
		//remove(temp);
	}
}
