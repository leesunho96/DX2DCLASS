#include "stdafx.h"
#include "Device.h"



/*
		DX : �޼����� ��ǥ�� : �޼� �������� �׷��߸� ���������� �׷���, �׷��� ���� ��� ���������� �׷����� ����.
		���� �ε����� �߿��ϴ�.
*/

/*
		Effect.fx : layout ������� ����
*/
ID3D11Buffer* vertexBuffer;



struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Shader* shader;

Vertex vertices[6];

void InitScene()
{
	shader = new Shader(L"../_Shaders/004_Effect.fx");

	// ù���� �ﰢ��, ���� �ε��� ������ �߿��ϴ�.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// �ι��� �ﰢ��
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Color = D3DXVECTOR3(1, 1, 1);
	vertices[1].Color = D3DXVECTOR3(1, 1, 1);

	vertices[2].Color = D3DXVECTOR3(1, 1, 1);
	vertices[3].Color = D3DXVECTOR3(1, 1, 1);

	vertices[4].Color = D3DXVECTOR3(1, 1, 1);
	vertices[5].Color = D3DXVECTOR3(1, 1, 1);
	
	vertexSize = ARRAYSIZE(vertices);


	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexSize;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}



}

void DestroyScene()
{
	delete shader;
	vertexBuffer->Release();
}

void Update()
{
	if (Key->Press('A') == true)
		vertices[0].Position.x -= 0.001f;
	else if (Key->Press('D') == true)
		vertices[0].Position.x += 0.001f;

	if (Key->Press('W') == true)
		vertices[0].Position.y += 0.001f;
	else if (Key->Press('S') == true)
		vertices[0].Position.y -= 0.001f;

	// updateSubresource : cpu�� ���� �ɱ� ������ ����. => �����ؾ���.
	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0
	);



}
/*
	�׶��̼��� ���������̷����
*/
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		// IA SET,  ContextDevice setting �ܰ�
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		shader->Draw(0, 0, 6);
		//DeviceContext->Draw(vertexSize, 0);
	}
	SwapChain->Present(0, 0);
}
