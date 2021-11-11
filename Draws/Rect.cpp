#include "stdafx.h"
#include "Rect.h"

Rect::Rect(wstring shaderFile, wstring imgFile)
	:position(0, 0), scale(200, 200)
{
	CreateBuffer(shaderFile, imgFile);
	UpdateWorld();
}

Rect::Rect(wstring shaderFile, wstring imgFile, D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:position(position), scale(scale)
{
	CreateBuffer(shaderFile, imgFile);
	UpdateWorld();
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(srv);
}

void Rect::ViewProjection(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
	UpdateWorld();
}

void Rect::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
	UpdateWorld();
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
	shader->Draw(0, 0, 6);


}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 & vec)
{
	position = vec;

	UpdateWorld();
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

	UpdateWorld();
}

void Rect::CreateBuffer(wstring shaderFile, wstring imgFile)
{
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(0, 1);
	vertices[1].Uv = D3DXVECTOR2(0, 0);
	vertices[2].Uv = D3DXVECTOR2(1, 1);
	vertices[3].Uv = D3DXVECTOR2(1, 1);
	vertices[4].Uv = D3DXVECTOR2(0, 0);
	vertices[5].Uv = D3DXVECTOR2(1, 0);

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
	//Create SRV
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			Device, imgFile.c_str(), NULL, NULL, &srv, NULL
		);
		assert(SUCCEEDED(hr));
	}
	shader = new Shader(shaderFile);
	shader->AsShaderResource("Map")->SetResource(srv);
}

void Rect::UpdateWorld()
{
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);

	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);
}


RECT Rect::GetWorldLocation()
{
	D3DXVECTOR4 WorldPosition[2];
	D3DXVec3Transform(&WorldPosition[0], &vertices[0].Position, &W);
	D3DXVec3Transform(&WorldPosition[1], &vertices[5].Position, &W);

	RECT result;
	result.left = WorldPosition[0].x;
	result.top = WorldPosition[0].y;
	result.right = WorldPosition[1].x;
	result.bottom = WorldPosition[1].y;

	return result;
}