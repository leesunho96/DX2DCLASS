#include "stdafx.h"
#include "Line.h"
#include "Objects/Marker.h"

Line::Line(Marker * a, Marker * b) : startpos(a), endPos(b)
{
	boundShader = new Shader(Shaders + L"014_Bounding.fx");
	vertices[0].Position = D3DXVECTOR3(a->Position().x, a->Position().y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(b->Position().x, b->Position().y, 0.0f);

	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Line::~Line()
{
	SAFE_DELETE(boundShader);
	SAFE_RELEASE(boundVertexBuffer);
}

void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	vertices[0].Position = D3DXVECTOR3(startpos->Position().x, startpos->Position().y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(endPos->Position().x, endPos->Position().y, 0.0f);

	
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));
	}

	boundShader->AsMatrix("View")->SetMatrix(V);
	boundShader->AsMatrix("Projection")->SetMatrix(P);

	
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	boundShader->AsMatrix("World")->SetMatrix(world);
}

void Line::Render()
{
	UINT stride = sizeof(BoundVertex);
	UINT offset = 0;
	
	DeviceContext->IASetVertexBuffers(0, 1, &boundVertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	
	boundShader->Draw(0, bistouch ? 1 : 0, 2);
}
