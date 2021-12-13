#include "stdafx.h"
#include "Line.h"
#include "Objects/Marker.h"
#include "Renders/Sprite.h"

Line::Line(Marker * a, Marker * b) : startpos(a), endPos(b)
{
	boundShader = new Shader(Shaders + L"014_Bounding.fx");
	vertices[0].Position = D3DXVECTOR3(a->Position().x, a->Position().y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(b->Position().x, b->Position().y, 0.0f);

	pastVertices[0].Position = D3DXVECTOR3(a->Position().x, a->Position().y, 0.0f);
	pastVertices[1].Position = D3DXVECTOR3(b->Position().x, b->Position().y, 0.0f);
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

	if(!(pastVertices[0].Position == vertices[0].Position && pastVertices[1].Position == vertices[1].Position))
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
	pastVertices[0].Position = vertices[0].Position;
	pastVertices[0].Position = vertices[1].Position;	  

	lineEquation = GetLineEquastion();

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
	ImGui::LabelText("LineEquation", "%.0f , %.0f, %.0f", lineEquation.x, lineEquation.y, lineEquation.z);
	
}

bool Line::CollisionTest(Sprite * input)
{
	bool result = IsCollide(input);
	bistouch = result ? true : false;		
	return false;
}


bool Line::IsCollide(Sprite * input)
{
	D3DXVECTOR2 texturesize = input->TextureSize();
	D3DXVECTOR2 position = input->Position();
	D3DXVECTOR2 Scale = input->Scale();

	texturesize.x *= Scale.x;
	texturesize.y *= Scale.y;

	D3DXVECTOR2	rightUp   = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	D3DXVECTOR2	rightDown = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	D3DXVECTOR2	leftUp    = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	D3DXVECTOR2	leftDown  = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	   	  



	int zeroNum = 0;
	int positiveNum = 0;


	// �Ÿ��� 0�� ���� �Ÿ��� ����� ��� �� ��츦 üũ.
	// �Ÿ��� 0�� ��찡 �ϳ��� �ִ� ��� �浹.
	// �Ÿ��� ����� ��찡 0 | 4 �ΰ�� �浹���� ����.
	// �Ÿ��� ����� ��찡 ���� ���̽��� �ƴѰ�� �浹

	GetDistanceBetweenLineAndPoint(lineEquation, rightUp)   == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, rightUp)   > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, rightDown) == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, rightDown) > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, leftUp)    == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, leftUp)    > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, leftDown)  == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, leftDown)  > 0 ? positiveNum++ : positiveNum;

	

	// ��������Ʈ�� �� �������� �ϳ��� �������� �Ÿ��� 0�̸� ������ ��������Ʈ�� �浹.
	if (zeroNum != 0)
	{
		return true;
	}

	// ��������Ʈ�� �� �������� ������ �Ÿ��� ��� ���(4)�̰ų� ��� ����(0)�̸� �浹���� ����. �׷��� ���� ���(1, 2, 3) �浹.
	if (positiveNum == 0 || positiveNum == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

float Line::GetSlope()
{
	return (vertices[0].Position.y - vertices[1].Position.y) / (vertices[0].Position.x - vertices[1].Position.x);
}

D3DXVECTOR3 Line::GetLineEquastion()
{
	D3DXVECTOR3 temp;
	float slope = GetSlope();
	
	//	y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1
	// slope * x 
	//- y 
	//- slope * x1 + y1

	temp.x = slope;
	temp.y = -1;
	temp.z = -slope * vertices[0].Position.x + vertices[0].Position.y;

	return temp;
}

float Line::GetDistanceBetweenLineAndPoint(D3DXVECTOR3 line, D3DXVECTOR2 point)
{
	//if (line.x == 0 && line.y == 0)
	//	return -D3D11_FLOAT32_MAX + 1;
	return (line.x * point.x) + (line.y * point.y) + line.z;
}
