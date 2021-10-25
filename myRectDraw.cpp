#include "stdafx.h"
#include "myRectDraw.h"

myRectDraw::myRectDraw()
{
	shader = new Shader(L"../_Shaders/005_WVP.fx");
	// ù���� �ﰢ��, ���� �ε��� ������ �߿��ϴ�.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// �ι��� �ﰢ��
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

	D3DXVECTOR3 eye(0, 0, -1); // z : ����, ���� ī�޶� ������ �ʵ���. ȭ�鿡�� �Ⱥ��̴� ��ġ. ���� �����ϴ� ������ 2d
	D3DXVECTOR3 at(0, 0, 0); // at : ī�޶� �ٶ󺸴� ����. (0, 0, -1)���� (0, 0, 0)�� �ٶ�
	D3DXVECTOR3 up(0, 1, 0); // ��� ���� �˷���
	D3DXMatrixLookAtLH(&V, &eye, &at, &up); // LeftHanded��ǥ�� �ش� ���� �ٶ�.
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
