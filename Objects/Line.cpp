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


	if (vertices[0].Position.x >= vertices[1].Position.x)
	{
		swap(vertices[0], vertices[1]);
		swap(pastVertices[0], pastVertices[1]);
	}

	//Create Vertex Buffer
	if (!(pastVertices[0].Position == vertices[0].Position && pastVertices[1].Position == vertices[1].Position))
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;
		boundVertexBuffer->Release();
		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));

	}
	pastVertices[0].Position = vertices[0].Position;
	pastVertices[0].Position = vertices[1].Position;	  

	lineEquation = GetLineEquastion();
	angle = GetDegree();
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
	ImGui::LabelText("Angle", "%.0f", angle);
}

bool Line::CollisionTest(Sprite * input)
{
	bool result = IsCollide(input);
	bistouch = result == true ? true : false;
	return bistouch;
}

float Line::GetDistance(Sprite * sprite)
{
	D3DXVECTOR2 point = sprite->Position();	
	return GetDistance(point);
}

float Line::GetDistance(D3DXVECTOR2 point)
{
	return (lineEquation.x * point.x) + (lineEquation.y * point.y) + lineEquation.z;	
}

float Line::GetDegree()
{
	//D3DXVECTOR2 presentDegree = D3DXVECTOR2(lineEquation.x, lineEquation.y);
	//float resultdegree = -presentDegree.y / presentDegree.x;
	//D3DXVECTOR2 UP = D3DXVECTOR2(0, 1);
	//D3DXVECTOR2 Degree = D3DXVECTOR2(1, resultdegree);
	
	//return asin((UP.x * Degree.y - UP.y * Degree.x) / D3DXVec2Length(&UP) * D3DXVec2Length(&Degree));	

	float dy = vertices[1].Position.y - vertices[0].Position.y;
	float dx = vertices[1].Position.x - vertices[0].Position.x;

	float result = atan2(dy, dx) * (180.0f / Math::PI);

	if (result > 90.0f)
	{
		result = result - 180.0f;
	}
	else if (result < -90.0f)
	{
		result = result +180.0f;
	}
	else
		result = result;
	return result;
}

bool Line::IsCollide(Sprite * input)
{
	D3DXVECTOR2 texturesize = input->TextureSize();
	D3DXVECTOR2 position = input->Position();
	D3DXVECTOR2 Scale = input->Scale();

	texturesize.x *= Scale.x;
	texturesize.y *= Scale.y;
	SpriteStatus spritestatus;

	spritestatus.rightUp   = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	spritestatus.rightDown = D3DXVECTOR2(position.x + texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	spritestatus.leftUp    = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y + texturesize.y * 0.5f);
	spritestatus.leftDown  = D3DXVECTOR2(position.x - texturesize.x * 0.5f, position.y - texturesize.y * 0.5f);
	   	  
	if (!IsInArea(spritestatus))
		return false;


	int zeroNum = 0;
	int positiveNum = 0;


	//if(vertices[0].Position.x )


	// �Ÿ��� 0�� ���� �Ÿ��� ����� ��� �� ��츦 üũ.
	// �Ÿ��� 0�� ��찡 �ϳ��� �ִ� ��� �浹.
	// �Ÿ��� ����� ��찡 0 | 4 �ΰ�� �浹���� ����.
	// �Ÿ��� ����� ��찡 ���� ���̽��� �ƴѰ�� �浹

	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightUp)   == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightUp)   > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightDown) == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.rightDown) > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftUp)    == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftUp)    > 0 ? positiveNum++ : positiveNum;
	GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftDown)  == 0.0f ? zeroNum++ : GetDistanceBetweenLineAndPoint(lineEquation, spritestatus.leftDown)  > 0 ? positiveNum++ : positiveNum;

	

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


	if (pos.y > ypos1 && pos.y < ypos2)
		return true;
	else
		return false;
}

bool Line::IsLinePointInSpriteWidth(SpriteStatus spritestatus)
{
	float left = spritestatus.leftDown.x;
	float right = spritestatus.rightDown.x;
	float bottom = spritestatus.leftDown.y;
	float height = spritestatus.leftUp.y;

	if (vertices[0].Position.x <= right && vertices[0].Position.x >= left)
	{
		
	}

	return true;
}

bool Line::IsLinePointInSpriteHeight(SpriteStatus spritestatus)
{
	return false;
}

bool Line::IsInArea(SpriteStatus input)
{
	// �÷��̾��� �� ������ ��ǥ�� line �� �׸��� �簢�� ���ο� �ִ� ��� �浹 ����.
	bool rightup   = IsInAreaX(input.rightUp)   && IsInAreaY(input.rightUp);
	bool rightdown = IsInAreaX(input.rightDown) && IsInAreaY(input.rightDown);
	bool leftup    = IsInAreaX(input.leftUp)    && IsInAreaY(input.leftUp);
	bool leftdown  = IsInAreaX(input.leftDown)  && IsInAreaY(input.leftDown);

	return rightup || rightdown || leftup || leftdown /*|| inWidth || inHeight*/ ? true : false;
}



float Line::GetSlope()
{
	if (vertices[0].Position.x == vertices[1].Position.x)
	{
		return 90.0f;
	}
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
	//if (line.x == 0)
	//	return point.x + line.z / line.y;
	if (line.y == 0)
		return point.y + line.z / line.x;
	return (line.x * point.x) + (line.y * point.y) + line.z;
}
