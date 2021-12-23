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

// for DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

// ImGUI
#include <imgui.h>
#include <imguiDx11.h>


// imgui : Image G
#pragma comment(lib, "imgui.lib")

#include "Systems/Keyboard.h"
#include "Systems/Time.h"
#include "Systems/DirectWrite.h"
#include "Systems/CMouse.h"
#include "Systems/StopWatch.h"

#include "Renders/Shader.h"
#include "Renders/Rect.h"
#include "Renders/Sprite.h"
#include "Renders/Clip.h"
#include "Renders/Animation.h"

#include "Utilities/Math.h"
#include "Utilities/Path.h"
#include "Utilities/String.h"


#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = NULL; } }

const unsigned char PressNothing = 0 << 0;	// 00000001  W를 누른 상태
const unsigned char PressW       = 1 << 0;	// 00000001  W를 누른 상태
const unsigned char PressA       = 1 << 1;	// 00000010  A를 누른 상태
const unsigned char PressS       = 1 << 2;	// 00000100  S를 누른 상태
const unsigned char PressD	     = 1 << 3;	// 00001000  D를 누른 상태
const unsigned char PressSpace   = 1 << 4;	// 00010000  Space를 누른 상태

extern UINT Width;
extern UINT Height;


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
extern CMouse* Mouse;