#include "stdafx.h"
#include "Device.h"
/*
		DX : 왼손잡이 좌표계 : 왼손 방향으로 그려야만 정상적으로 그려짐, 그렇지 않은 경우 정상적으로 그려지지 않음.
		정점 인덱싱이 중요하다.
		Effect.fx : layout 사용하지 않음
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

	// 첫번쨰 삼각형, 정점 인덱스 순서도 중요하다.
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	// 두번쨰 삼각형
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);


	// 첫번쨰 삼각형, 정점 인덱스 순서도 중요하다.
	vertices2[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices2[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices2[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);// 두번쨰 삼각형
	vertices2[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	/*
		변수로 색상 이전,  GUI로도 가능
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
	// 해당 행렬 초기화. 정방행렬
	//D3DXMatrixIdentity(&W);
	//D3DXMatrixIdentity(&V);
	//D3DXMatrixIdentity(&P);

	// World = S * R * T
	D3DXMATRIX S, T;


	D3DXMatrixScaling(&S, 100, 100, 1); // 스케일 변경, 항상 초기값은 1. 0=> 렌더링 안됨.
	D3DXMatrixTranslation(&T, position.x, position.y, 0); //변환행렬 생성, 

	W = S * T;

	D3DXMatrixScaling(&S, 50, 50, 1); // 스케일 변경, 항상 초기값은 1. 0=> 렌더링 안됨.
	D3DXMatrixTranslation(&T, position2.x, position2.y, 0); //

	W2 = S * T;

	//View
	D3DXVECTOR3 eye(0, 0, -1); // z : 깊이, 실제 카메라가 보이지 않도록. 화면에서 안보이는 위치. 현재 제작하는 게임은 2d
	D3DXVECTOR3 at(0, 0, 0); // at : 카메라가 바라보는 방향. (0, 0, -1)에서 (0, 0, 0)을 바라봄
	D3DXVECTOR3 up(0, 1, 0); // 상단 방향 알려줌
	D3DXMatrixLookAtLH(&V, &eye, &at, &up); // LeftHanded좌표로 해당 방향 바라봄.

	//projection 세팅
	D3DXMatrixOrthoOffCenterLH(&P, 0 , (float)Width, 0, (float)Height, -1, 1);

	// 각각의 매트릭스를 shader에 넘겨줌
//	shader->AsMatrix("World")->SetMatrix(W);
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);


	// shader에 값 넘기는 함수
	//("shader에 넘길 변수명(shader에 저장된 이름)")->SetFloatVector(scene에서 정의한 벡터 color)
//	shader->AsVector("Color")->SetFloatVector(color);

	// updateSubresource : Gpu에 락을 걸기 때문에 정지. => 지양해야함.
	//DeviceContext->UpdateSubresource
	//(
	//	vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0
	//);

	// W(World)V(View)P(Projection)
	/*
	공간 안에 물체를 넣고 공간을 이동시 동시에 움직임.
	공간을 회전/확대/축소시 내부의 물체도 동일하게 변경.
	로컬 좌표 : 현재 객체 자신의 좌표
	상대 좌표 : 월드 좌표와 로컬 좌표간의 차이
	월드 좌표 : 로컬 좌표가 들어갈 공간.

	V : 카메라가 바라보는 시점. 물체를 비추는 공간
	P : Projection.

	공간 : 4x4 Matrix(행렬) 
	1 0 0 0
	0 1 0 0
	0 0 1 0 
	0 0 0 1
	1.1, 1.2, 1.3 = > 크기(해당 행렬 공간에서의 크기, 초기값 : 1 (크기가 0이면 안보임.))

	4.1, 4.2, 4.3, 4.4 => x, y, z, W
	-> 정방행렬. 행렬의 초기값. Matrix Identity.
	-> 행 우선. 실제로는 DX 10부터는 열우선으로 변경, 대부분 책이 행우선으로 설명하고 있기 때문에 해당 방식으로 진행.
	           => OpenGL : 행우선.


	선형 변환 (x = 변환할 각도)
	cos x   -sin x | X => X' =  cosx * X - sinx * Y
	sin x    cos x | Y => Y' =  sinx * X + cosx * Y 
	*/

}
/*
	그라데이션은 선형보간이루어짐
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

		// IA SET,  ContextDevice setting 단계
		shader->AsMatrix("World")->SetMatrix(W);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		shader->Draw(0, 0, 6);

		shader->AsMatrix("World")->SetMatrix(W2);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);
		shader->Draw(0, 0, 6);
		//DeviceContext->Draw(vertexSize, 0);
	}
	// UI는 기존 화면 렌더링 완료 후 그 위에 렌더링.
	ImGui::Render();
	SwapChain->Present(0, 0);
}
