#pragma once
#include <windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
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


// imgui : Image G
#pragma comment(lib, "imgui.lib")


#include "Renders/Shader.h"
#include "Systems/Keyboard.h"
#include "Systems/Time.h"

#include "Draws/Rect.h"
#include "Draws/Sprite.h"

#include "Utilities/Math.h"
#include "Utilities/Path.h"
#include "Utilities/String.h"


#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = NULL; } }

const UINT Width = 800;
const UINT Height = 600;
const UINT BaseX = 160;
const UINT BaseY = 575;
#define MAXARRHEIGHT  15

const wstring Textures = L"../_Textures/";
const wstring Shaders = L"../_Shaders/";


// 타 파일의 전역변수를 사용 할 수 있도록 함.
extern HWND Hwnd;
extern wstring Title;

extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern Keyboard* Key;
extern Time* Timer;
