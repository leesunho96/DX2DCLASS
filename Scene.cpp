#include "stdafx.h"
#include "Device.h"



/*
		DX : 왼손잡이 좌표계 : 왼손 방향으로 그려야만 정상적으로 그려짐, 그렇지 않은 경우 정상적으로 그려지지 않음.
		정점 인덱싱이 중요하다.
*/

/*
		Effect.fx : layout 사용하지 않음
*/
ID3D11Buffer* vertexBuffer;



struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Shader* shader;
D3DXCOLOR color = D3DXCOLOR(1, 1, 0, 1);
Vertex vertices[6];


void InitScene()
{
	//int a = 10;
	//assert(a > 10);

	shader = new Shader(L"../_Shaders/004_Effect.fx");

	// 첫번쨰 삼각형, 정점 인덱스 순서도 중요하다.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// 두번쨰 삼각형
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);


	/*
		변수로 색상 이전,  GUI로도 가능
	*/
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

	// shader에 값 넘기는 함수
	//("shader에 넘길 변수명(shader에 저장된 이름)")->SetFloatVector(scene에서 정의한 벡터 color)
	shader->AsVector("Color")->SetFloatVector(color);

	// updateSubresource : cpu에 락을 걸기 때문에 정지. => 지양해야함.
	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0
	);



}
/*
	그라데이션은 선형보간이루어짐
*/
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::ColorEdit4("Color", (float*)&color, 0);


		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		// IA SET,  ContextDevice setting 단계
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		shader->Draw(0, 0, 6);
		//DeviceContext->Draw(vertexSize, 0);
	}
	// UI는 기존 화면 렌더링 완료 후 그 위에 렌더링.
	ImGui::Render();
	SwapChain->Present(0, 0);
}
