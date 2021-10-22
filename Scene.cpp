#include "stdafx.h"
#include "Device.h"
/*
		DX : �޼����� ��ǥ�� : �޼� �������� �׷��߸� ���������� �׷���, �׷��� ���� ��� ���������� �׷����� ����.
		���� �ε����� �߿��ϴ�.
		Effect.fx : layout ������� ����
*/

ID3D11Buffer* vertexBuffer;
ID3D11Buffer* vertexBuffer2;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Vertex vertices[6];
Vertex vertices2[6];

Shader* shader;
D3DXCOLOR color = D3DXCOLOR(1, 0, 0, 1);
// matrix : float16
D3DXMATRIX W, W2; // World
D3DXMATRIX V, P; // View, P
static int vertexSize = 0;
static int vertexSize2 = 0;
void InitScene()
{
	//int a = 10;
	//assert(a > 10);

	shader = new Shader(L"../_Shaders/005_WVP.fx");

	// ù���� �ﰢ��, ���� �ε��� ������ �߿��ϴ�.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// �ι��� �ﰢ��
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);


	// ù���� �ﰢ��, ���� �ε��� ������ �߿��ϴ�.
	vertices2[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices2[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices2[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);// �ι��� �ﰢ��
	vertices2[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	/*
		������ ���� ����,  GUI�ε� ����
	*/
	vertices[0].Color = D3DXVECTOR3(1, 1, 1);
	vertices[1].Color = D3DXVECTOR3(1, 1, 1);

	vertices[2].Color = D3DXVECTOR3(1, 1, 1);
	vertices[3].Color = D3DXVECTOR3(1, 1, 1);

	vertices[4].Color = D3DXVECTOR3(1, 1, 1);
	vertices[5].Color = D3DXVECTOR3(1, 1, 1);

	vertices2[0].Color = D3DXVECTOR3(0, 1, 1);
	vertices2[1].Color = D3DXVECTOR3(0, 1, 1);
	vertices2[2].Color = D3DXVECTOR3(0, 1, 1);
	vertices2[3].Color = D3DXVECTOR3(0, 1, 1);
	vertices2[4].Color = D3DXVECTOR3(0, 1, 1);
	vertices2[5].Color = D3DXVECTOR3(0, 1, 1);
	
	vertexSize = ARRAYSIZE(vertices);
	vertexSize2 = ARRAYSIZE(vertices2);

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

	//Create Vertex Buffer2
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexSize;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices2;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer2);
		assert(SUCCEEDED(hr));
	}
}

void DestroyScene()
{
	delete shader;
	vertexBuffer->Release();
}

D3DXVECTOR2 position = D3DXVECTOR2(100, 100);
D3DXVECTOR2 position2 = D3DXVECTOR2(100, 100);

void Update()
{
	// �ش� ��� �ʱ�ȭ. �������
	//D3DXMatrixIdentity(&W);
	//D3DXMatrixIdentity(&V);
	//D3DXMatrixIdentity(&P);

	// World = S * R * T
	D3DXMATRIX S, T;


	D3DXMatrixScaling(&S, 100, 100, 1); // ������ ����, �׻� �ʱⰪ�� 1. 0=> ������ �ȵ�.
	D3DXMatrixTranslation(&T, position.x, position.y, 0); //��ȯ��� ����, 

	W = S * T;

	D3DXMatrixScaling(&S, 50, 50, 1); // ������ ����, �׻� �ʱⰪ�� 1. 0=> ������ �ȵ�.
	D3DXMatrixTranslation(&T, position2.x, position2.y, 0); //

	W2 = S * T;

	//View
	D3DXVECTOR3 eye(0, 0, -1); // z : ����, ���� ī�޶� ������ �ʵ���. ȭ�鿡�� �Ⱥ��̴� ��ġ. ���� �����ϴ� ������ 2d
	D3DXVECTOR3 at(0, 0, 0); // at : ī�޶� �ٶ󺸴� ����. (0, 0, -1)���� (0, 0, 0)�� �ٶ�
	D3DXVECTOR3 up(0, 1, 0); // ��� ���� �˷���
	D3DXMatrixLookAtLH(&V, &eye, &at, &up); // LeftHanded��ǥ�� �ش� ���� �ٶ�.

	//projection ����
	D3DXMatrixOrthoOffCenterLH(&P, 0 , (float)Width, 0, (float)Height, -1, 1);

	// ������ ��Ʈ������ shader�� �Ѱ���
//	shader->AsMatrix("World")->SetMatrix(W);
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);


	// shader�� �� �ѱ�� �Լ�
	//("shader�� �ѱ� ������(shader�� ����� �̸�)")->SetFloatVector(scene���� ������ ���� color)
//	shader->AsVector("Color")->SetFloatVector(color);

	// updateSubresource : Gpu�� ���� �ɱ� ������ ����. => �����ؾ���.
	//DeviceContext->UpdateSubresource
	//(
	//	vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0
	//);

	// W(World)V(View)P(Projection)
	/*
	���� �ȿ� ��ü�� �ְ� ������ �̵��� ���ÿ� ������.
	������ ȸ��/Ȯ��/��ҽ� ������ ��ü�� �����ϰ� ����.
	���� ��ǥ : ���� ��ü �ڽ��� ��ǥ
	��� ��ǥ : ���� ��ǥ�� ���� ��ǥ���� ����
	���� ��ǥ : ���� ��ǥ�� �� ����.

	V : ī�޶� �ٶ󺸴� ����. ��ü�� ���ߴ� ����
	P : Projection.

	���� : 4x4 Matrix(���) 
	1 0 0 0
	0 1 0 0
	0 0 1 0 
	0 0 0 1
	1.1, 1.2, 1.3 = > ũ��(�ش� ��� ���������� ũ��, �ʱⰪ : 1 (ũ�Ⱑ 0�̸� �Ⱥ���.))

	4.1, 4.2, 4.3, 4.4 => x, y, z, W
	-> �������. ����� �ʱⰪ. Matrix Identity.
	-> �� �켱. �����δ� DX 10���ʹ� ���켱���� ����, ��κ� å�� ��켱���� �����ϰ� �ֱ� ������ �ش� ������� ����.
	           => OpenGL : ��켱.


	���� ��ȯ (x = ��ȯ�� ����)
	cos x   -sin x | X => X' =  cosx * X - sinx * Y
	sin x    cos x | Y => Y' =  sinx * X + cosx * Y 
	*/

}
/*
	�׶��̼��� ���������̷����
*/
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//ImGui::ColorEdit4("Color", (float*)&color, 0);

		ImGui::SliderFloat("X", &position.x, 100, Width - 100);
		ImGui::SliderFloat("Y", &position.y, 100, Height - 100);

		ImGui::SliderFloat("X2", &position2.x, 100, Width - 100);
		ImGui::SliderFloat("Y2", &position2.y, 100, Height - 100);


		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// IA SET,  ContextDevice setting �ܰ�
		shader->AsMatrix("World")->SetMatrix(W);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		shader->Draw(0, 0, 6);

		shader->AsMatrix("World")->SetMatrix(W2);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);
		shader->Draw(0, 0, 6);
		//DeviceContext->Draw(vertexSize, 0);
	}
	// UI�� ���� ȭ�� ������ �Ϸ� �� �� ���� ������.
	ImGui::Render();
	SwapChain->Present(0, 0);
}
