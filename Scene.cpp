#include "stdafx.h"
#include "Device.h"



/*
		DX : 왼손잡이 좌표계 : 왼손 방향으로 그려야만 정상적으로 그려짐, 그렇지 않은 경우 정상적으로 그려지지 않음.
		정점 인덱싱이 중요하다.
*/
ID3D11Buffer* vertexBuffer;
ID3D11InputLayout* inputLayout;
D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	,{"COLOR",0, DXGI_FORMAT_R32G32B32_FLOAT,0,12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

static float playerSize = 0.1f;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Vertex* vertices;

float getRandomAbsoluteFloat(int maximum)
{
	//srand(time(NULL));
	rand();
	int temp = rand() % maximum + 1;
	float result = temp;
	result /= 1000;
	return result;
}

float getRandomFloat(int maximum)
{
	return rand() % 2 == 1 ? getRandomAbsoluteFloat(maximum) : -getRandomAbsoluteFloat(maximum);
}


bool isOverLap(int rectindex1, int rectindex2)
{
	float rc1_left = vertices[6 * rectindex1 + 1].Position.x; // 1.x
	float rc1_up = vertices[6 * rectindex1 + 1].Position.y; // 1.x
	float rc1_down = vertices[6 * rectindex1 + 2].Position.y; // 2.y
	float rc1_right = vertices[6 * rectindex1 + 2].Position.x; // 2.x

	float rc2_left = vertices[6 * rectindex2 + 1].Position.x; // 7.x
	float rc2_up = vertices[6 * rectindex2 + 1].Position.y; // 7.y
	float rc2_right = vertices[6 * rectindex2 + 2].Position.x; // 8.x
	float rc2_down = vertices[6 * rectindex2 + 2].Position.y; // 8.y


	//RECT square1;// = { rc1_left, rc1_up, rc1_right, rc1_down };
	//RECT square2;// = { rc2_left, rc2_up, rc2_right, rc2_down };
	//RECT temp;

	//SetRect(&square1, (long)rc1_left, (long)rc1_up, (long)rc1_right, (long)rc1_down);
	//SetRect(&square2, (long)rc2_left, (long)rc2_up, (long)rc2_right, (long)rc2_down);

	//if (!IntersectRect(&temp, &square1, &square2))
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

	if (rc1_right >= rc2_left && rc1_down <= rc2_up && rc1_left <= rc2_right && rc1_up >= rc2_down)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void moveOut(int index)
{
	vertices[6 * index].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertices[6 * index + 1].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertices[6 * index + 2].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertices[6 * index + 3].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertices[6 * index + 4].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertices[6 * index + 5].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

	//vertices[6 * index].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//vertices[6 * index + 1].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//vertices[6 * index + 2].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//vertices[6 * index + 3].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//vertices[6 * index + 4].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//vertices[6 * index + 5].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
D3DXVECTOR3 getRandomColor()
{

	D3DXVECTOR3 _001(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 _010(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 _011(0.0f, 1.0f, 1.0f);
	D3DXVECTOR3 _100(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 _101(1.0f, 0.0f, 0.1f);
	D3DXVECTOR3 _110(1.0f, 1.0f, 0.0f);

	rand();
	rand();

	switch (rand() % 5 + 1)
	{
	case 1:
		return _001;
	case 2:
		return _010;
	case 3:
		return _011;
	case 4:
		return _100;
	case 5:
		return _101;
	case 6:
		return _110;
	}
	return D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void makeSquare(Vertex* vertexArr, int index)
{
	D3DXVECTOR3 baseVector = D3DXVECTOR3(/*-0.5f, -0.5f, 0.0f);//*/getRandomFloat(800), getRandomFloat(800), 0.0f);
	D3DXVECTOR3 baseColor = getRandomColor();
	float length = 0.3f;//getRandomAbsoluteFloat(500);


	for (size_t i = 1; i < index; i++)
	{
		vertexArr[6 * index].Position = baseVector;
		vertexArr[6 * index + 1].Position = baseVector + D3DXVECTOR3(0.0f, length, 0.0f);
		vertexArr[6 * index + 2].Position = baseVector + D3DXVECTOR3(length, 0.0f, 0.0f);
		vertexArr[6 * index + 3].Position = vertexArr[6 * index + 2].Position;
		vertexArr[6 * index + 4].Position = vertexArr[6 * index + 1].Position;
		vertexArr[6 * index + 5].Position = baseVector + D3DXVECTOR3(length, length, 0.0f);

		for (size_t j = 0; j < i; j++)
		{
			if (isOverLap(j, i))
			{
				i--;
				break;
			}
		}
	}



	// 각 정점의 색 초기화.
	for (size_t i = 0; i < 6; i++)
	{
		vertexArr[6 * index + i].Color = baseColor;//getRandomColor();
	}

}

void initPlayer(D3DXVECTOR3 inputBaseVector, float length = 0.5f)
{
	D3DXVECTOR3 baseVector = inputBaseVector;
	//float length = 0.5f;//getRandomAbsoluteFloat(500);
	vertices[0].Position = baseVector;
	vertices[1].Position = baseVector + D3DXVECTOR3(0.0f, length, 0.0f);
	vertices[2].Position = baseVector + D3DXVECTOR3(length, 0.0f, 0.0f);
	vertices[3].Position = vertices[2].Position;
	vertices[4].Position = vertices[1].Position;
	vertices[5].Position = baseVector + D3DXVECTOR3(length, length, 0.0f);

	for (size_t i = 0; i < 6; i++)
	{
		vertices[i].Color = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

int squareNum = 0;

void InitScene()
{
	squareNum = 6;
	vertexSize = 6 * squareNum; //ARRAYSIZE(vertices);
	vertices = new Vertex[vertexSize];

	initPlayer(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), playerSize);


	for (int i = 1; i < squareNum; i++)
	{
		makeSquare(vertices, i);
	}

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

	//Create InputLayout
	{
		HRESULT hr = Device->CreateInputLayout
		(
			layoutDesc, ARRAYSIZE(layoutDesc), VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), &inputLayout
		);
		assert(SUCCEEDED(hr));
	}

}


void DestroyScene()
{
	inputLayout->Release();
	vertexBuffer->Release();
}

void Update()
{
	if (Key->Press('A') == true)
	{
		for (size_t i = 0; i < 6; i++)
		{
			vertices[i].Position.x -= 0.0005f;
		}
		//vertices[0].Position.x -= 0.0005f;
	}
	else if (Key->Press('D') == true)
	{
		for (size_t i = 0; i < 6; i++)
		{
			vertices[i].Position.x += 0.0005f;
		}
		//vertices[0].Position.x += 0.0005f;
	}

	if (Key->Press('W') == true)
	{
		for (size_t i = 0; i < 6; i++)
		{
			vertices[i].Position.y += 0.0005f;
		}
		//vertices[0].Position.y += 0.0005f;
	}
	else if (Key->Press('S') == true)
	{
		for (size_t i = 0; i < 6; i++)
		{
			vertices[i].Position.y -= 0.0005f;
		}
		//vertices[0].Position.y -= 0.0005f;
	}

	// 각 사각형이 서로 겹치는지 체크
	for (size_t i = 1; i < squareNum; i++)
	{
		if (isOverLap(0, i))
		{
			moveOut(i);
			playerSize += 0.1f;
			initPlayer(vertices[0].Position, playerSize);
		}
	}

	// updateSubresource : cpu에 락을 걸기 때문에 정지. => 지양해야함.
	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * vertexSize, 0
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
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);
		DeviceContext->Draw(vertexSize, 0);
	}
	SwapChain->Present(0, 0);
}
