#pragma once
#include <windows.h>
#include <assert.h>
#include <string>
using namespace std;

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dX10.h>
#include <d3dx10math.h>
#include <d3dx11effect.h>
#include <d3dcompiler.h>




#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "effects11d.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ImGUI
#include <imgui.h>
#include <imguiDx11.h>

#pragma comment(lib, "imgui.lib")


#include "Systems/Keyboard.h"
#include "Renders/Shader.h"

const UINT Width = 1024;
const UINT Height = 768;


// Ÿ ������ ���������� ��� �� �� �ֵ��� ��.
extern HWND Hwnd;
extern wstring Title;

extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern ID3D11VertexShader* VertexShader;
extern ID3D11PixelShader* PixelShader;
extern ID3D10Blob* VsBlob;
extern ID3D10Blob* PsBlob;

extern Keyboard* Key;