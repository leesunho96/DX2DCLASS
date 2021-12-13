#include "stdafx.h"
#include "Line.h"
#include "Objects/Marker.h"
#include "Renders/Sprite.h"

Line::Line(Marker * a, Marker * b) : startpos(a), endPos(b)
{
	boundShader = new Shader(Shaders + L"014_Bounding.fx");

	Marker* temp1 = a;
	Marker* temp2 = b;

	if (a->Position().x >= b->Position().x)
	{
		swap(temp1, temp2);
	}

	vertices[0].Position = D3DXVECTOR3(temp1->Position().x, temp1->Position().y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(temp2->Position().x, temp2->Position().y, 0.0f);

	pastVertices[0].Position = D3DXVECTOR3(temp1->Position().x, temp1->Position().y, 0.0f);
	pastVertices[1].Position = D3DXVECTOR3(temp2->Position().x, temp2->Position().y, 0.0f);
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
	SpriteStatus spritestatus;

	spritestatus.rightUp   = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	spritestatus.rightDown = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	spritestatus.leftUp    = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	spritestatus.leftDown  = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	   	  
	if (!IsInArea(spritestatus))
		return false;


	int zeroNum = 0;
	int positiveNum = 0;


	// 거리가 0인 경우와 거리가 양수인 경우 두 경우를 체크.
	// 거리가 0인 경우가 하나라도 있는 경우 충돌.
	// 거리가 양수인 경우가 0 | 4 인경우 충돌하지 않음.
	// 거리가 양수인 경우가 위의 케이스가 아닌경우 충돌

	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightUp)   == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightUp)   > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightDown) == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightDown) > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftUp)    == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftUp)    > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftDown)  == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftDown)  > 0 ? positiveNum++ : positiveNum;

	

	// 스프라이트의 네 꼭지점중 하나라도 직선과의 거리가 0이면 직선과 스프라이트는 충돌.
	if (zeroNum != 0)
	{
		return true;
	}

	// 스프라이트의 네 꼭지점과 직선의 거리가 모두 양수(4)이거나 모두 음수(0)이면 충돌하지 않음. 그렇지 않은 경우(1, 2, 3) 충돌.
	if (positiveNum == 0 || positiveNum == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Line::IsInAreaX(D3DXVECTOR2 pos)
{
	float xpos1, xpos2;

	if (vertices[0].Position.x >= vertices[1].Position.x)
	{
		xpos1 = vertices[1].Position.x;
		xpos2 = vertices[0].Position.x;
	}
	else
	{
		xpos1 = vertices[0].Position.x;
		xpos2 = vertices[1].Position.x;
	}


	if (pos.x > xpos1 && pos.x < xpos2)
		return true;
	else
		return false;
}

bool Line::IsInAreaY(D3DXVECTOR2 pos)
{
	float ypos1, ypos2;

	if (vertices[0].Position.y >= vertices[1].Position.y)
	{
		ypos1 = vertices[1].Position.y;
		ypos2 = vertices[0].Position.y;
	}
	else
	{
		ypos1 = vertices[0].Position.y;
		ypos2 = vertices[1].Position.y;
	}


	if (pos.x > ypos1 && pos.x < ypos2)
		return true;
	else
		return false;
}

bool Line::IsInArea(SpriteStatus input)
{
	bool rightup   = IsInAreaX(input.rightUp)   || IsInAreaY(input.rightUp);
	bool rightdown = IsInAreaX(input.rightDown) || IsInAreaY(input.rightDown);
	bool leftup    = IsInAreaX(input.leftUp)    || IsInAreaY(input.leftUp);
	bool leftdown  = IsInAreaX(input.leftDown)  || IsInAreaY(input.leftDown);

	return rightup || rightdown || leftup || leftdown ? true : false;
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
