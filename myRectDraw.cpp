#include "stdafx.h"
#include "myRectDraw.h"


void myRectDraw::initialize()
{
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	
	eye = D3DXVECTOR3(0, 0, -1); // z : 깊이, 실제 카메라가 보이지 않도록. 화면에서 안보이는 위치. 현재 제작하는 게임은 2d
	at = D3DXVECTOR3(0, 0, 0); // at : 카메라가 바라보는 방향. (0, 0, -1)에서 (0, 0, 0)을 바라봄
	up = D3DXVECTOR3(0, 1, 0); // 상단 방향 알려줌
}

D3DXVECTOR3 myRectDraw::GetRandomColor()
{
	D3DXVECTOR3 _001(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 _010(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 _011(0.0f, 1.0f, 1.0f);
	D3DXVECTOR3 _100(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 _101(1.0f, 0.0f, 1.0f);
	D3DXVECTOR3 _110(1.0f, 1.0f, 0.0f);


	D3DXVECTOR3 colors[6] = { _001, _010, _011, _100, _101, _110 };
	return colors[Math::Random(0, 5)];
}

myRectDraw::myRectDraw()
{
	shader = new Shader(L"../_Shaders/005_WVP.fx");


	// 첫번쨰 삼각형, 정점 인덱스 순서도 중요하다.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// 두번쨰 삼각형
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	
	
	setColor(GetRandomColor());
	initialize();
}

myRectDraw::myRectDraw(float left, float top, float right, float down)
{
	D3DXVECTOR3 vleft  = D3DXVECTOR3(0.1f, 0.0f, 0.0f) * left;
	D3DXVECTOR3 vright = D3DXVECTOR3(0.1f, 0.0f, 0.0f) * right;
	D3DXVECTOR3 vtop   = D3DXVECTOR3(0.0f, 0.1f, 0.0f) * top;
	D3DXVECTOR3 vdown  = D3DXVECTOR3(0.0f, 0.1f, 0.0f) * down;

	D3DXVECTOR3 left_down  = vleft  + vdown;
	D3DXVECTOR3 left_top   = vleft  + vtop;
	D3DXVECTOR3 right_down = vright + vdown;
	D3DXVECTOR3 right_top  = vright + vtop;

	vertices[0].Position = left_down;
	vertices[1].Position = left_top;
	vertices[2].Position = right_down;
	vertices[3].Position = right_down;
	vertices[4].Position = left_top;
	vertices[5].Position = right_top;

	setColor(GetRandomColor());
	initialize();
}

void myRectDraw::setPosition(D3DXVECTOR2 Position)
{
	this->position.x = Position.x;
	this->position.y = Position.y;
}

void myRectDraw::setColor(D3DXVECTOR3 color)
{
	for (size_t i = 0; i < 6; i++)
	{
		vertices[i].Color = color;
	}
}

void myRectDraw::setRandomColor()
{
	setColor(GetRandomColor());
}

void myRectDraw::Update()
{
	D3DXMatrixScaling(&S, 100, 100, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	W = S * T;
	D3DXMatrixLookAtLH(&V, &eye, &at, &up); // LeftHanded좌표로 해당 방향 바라봄.
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
}

void myRectDraw::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->AsMatrix("World")->SetMatrix(W);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	shader->Draw(0, 0, 6);
}

RECT myRectDraw::GetWorldRect()
{
	D3DXVec3Transform(&WorldPosition[0], &vertices[0].Position, &W);
	D3DXVec3Transform(&WorldPosition[1], &vertices[5].Position, &W);
	
	RECT result;
	result.left   = WorldPosition[0].x;
	result.top    = WorldPosition[0].y;
	result.right  = WorldPosition[1].x;
	result.bottom = WorldPosition[1].y;

	return result;
}

myRectDraw::~myRectDraw()
{
	delete shader;
	//vertexBuffer->Release();
}
