#include "stdafx.h"



void InitWindow(HINSTANCE hInstance, int ShowWnd);
void InitDirect3D(HINSTANCE hInstance);
void Destroy();

WPARAM Running();
LRESULT CALLBACK WndProc(HWND hWnd,	UINT msg, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////

void createPlayer();

void DeleteEnemys();

void DeletePlayer();

void InitScene();
void DestroyScene();
void Update();
void SetViewProjection();
void resetScore();
void RenderObjects();
void Render();