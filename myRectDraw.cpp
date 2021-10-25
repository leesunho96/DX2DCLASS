#include "stdafx.h"
#include "myRectDraw.h"

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

	vertices[0].Color = D3DXVECTOR3(0, 1, 1);
	vertices[1].Color = D3DXVECTOR3(0, 1, 1);
	vertices[2].Color = D3DXVECTOR3(0, 1, 1);
	vertices[3].Color = D3DXVECTOR3(0, 1, 1);
	vertices[4].Color = D3DXVECTOR3(0, 1, 1);
	vertices[5].Color = D3DXVECTOR3(0, 1, 1);

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
}

void myRectDraw::setPosition(D3DXVECTOR2 Position)
{
	this->position.x = Position.x;
	this->position.y = Position.y;
}

void myRectDraw::Update()
{
	D3DXMatrixScaling(&S, 100, 100, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	W = S * T;

	D3DXVECTOR3 eye(0, 0, -1); // z : 깊이, 실제 카메라가 보이지 않도록. 화면에서 안보이는 위치. 현재 제작하는 게임은 2d
	D3DXVECTOR3 at(0, 0, 0); // at : 카메라가 바라보는 방향. (0, 0, -1)에서 (0, 0, 0)을 바라봄
	D3DXVECTOR3 up(0, 1, 0); // 상단 방향 알려줌
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

myRectDraw::~myRectDraw()
{
	delete shader;
	vertexBuffer->Release();
}
