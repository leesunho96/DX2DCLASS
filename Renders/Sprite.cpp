#include "stdafx.h"
#include "Sprite.h"

//-----------------------------------------------------------------------------
//Sprite
//-----------------------------------------------------------------------------

Sprite::Sprite(wstring textureFile, wstring shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float endX, float endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);
}

void Sprite::Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	textureFile = spriteFile;

	bDrawBound = true;
	shader = new Shader(shaderFile);
	boundShader = new Shader(Shaders + L"014_Bounding.fx");

	srv = Sprites::Load(spriteFile);
	shader->AsShaderResource("Map")->SetResource(srv);


	Position(0, 0);
	Rotation(0, 0, 0);
	Scale(1, 1);
	D3DXMatrixIdentity(&world);

	bDrawCollision = false;

	HRESULT hr;
	D3DX11_IMAGE_INFO info;
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL);
	assert(SUCCEEDED(hr));

	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(startX, endY);
	vertices[1].Uv = D3DXVECTOR2(startX, startY);
	vertices[2].Uv = D3DXVECTOR2(endX, endY);
	vertices[3].Uv = D3DXVECTOR2(endX, endY);
	vertices[4].Uv = D3DXVECTOR2(startX, startY);
	vertices[5].Uv = D3DXVECTOR2(endX, startY);

	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;

	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;

	textureSize = D3DXVECTOR2(sizeX, sizeY);


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

	CreateBound();
}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);

	Sprites::Remove(textureFile);
}

void Sprite::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	boundShader->AsMatrix("View")->SetMatrix(V);
	boundShader->AsMatrix("Projection")->SetMatrix(P);

	D3DXMATRIX S, R, T;

	D3DXMatrixScaling(&S, textureSize.x * scale.x, textureSize.y * scale.y, 1);
	// 짐벌락 : 완전히 없애진 못함.
	// 오일러 / 쿼터니온 등
	// 한번에 돌리거나 사원소를 쓰거나. 백프로 없애지 못함.
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0);

	world = S * R * T;

	shader->AsMatrix("World")->SetMatrix(world);
	boundShader->AsMatrix("World")->SetMatrix(world);
}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);

	if (bDrawBound == true)
	{
		stride = sizeof(BoundVertex);
		offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &boundVertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		boundShader->Draw(0, bDrawCollision ? 1 : 0, 5);
	}
}


void Sprite::CreateBound()
{
	BoundVertex vertices[5];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 & vec)
{
	position = vec;
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
}



void Sprite::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Sprite::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;

}

void Sprite::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Sprite::RotationDegree(D3DXVECTOR3 & vec)
{
	vec.x = Math::ToRadian(vec.x);
	vec.y = Math::ToRadian(vec.y);
	vec.z = Math::ToRadian(vec.z);

	Rotation(vec);
}

D3DXVECTOR3 Sprite::RotationDegree()
{
	D3DXVECTOR3 vec;
	vec.x = Math::ToDegree(rotation.x);
	vec.y = Math::ToDegree(rotation.y);
	vec.z = Math::ToDegree(rotation.z);

	return vec;
}

bool Sprite::AABB(D3DXVECTOR2 position)
{

	return AABB(this, position);
}

bool Sprite::AABB(Sprite * b)
{

	return AABB(this, b);
}

// OBB(Object oriented Bounding Box) COLLISION

// AABB는 모든 축이 정렬된 sprite들에만 적용 가능 => 충돌 확인 하려는 스프라이트들이 평행해야 함
// AABB( Axis Aligned Bounding Box)는 축에 정렬된 상태이기 때문에
// 박스가 회전하지 않고 축 방향으로 이동만 하여 위치를 잡게 된다.
// 그러므로 AABB의 두가지 요소 Min, Max값을 이용하여 각각의 축에 대하여 1차원적인 비교만 하면 된다.
// OBB는 축이 정렬되어 있지 않은 sprite들 충돌 체크하는 방식.
// => 별개의 seperate axis를 생성 후, 해당 축에 각 sprite를 투영.
// seperate axis에 각 sprite의 position(중점)부터 가장 긴 가장자리를 투영한다.
// 그렇게 투영한 길이의 합을 구한다.
// 각 두개의 스프라이트의 중점사이의 벡터를 seperate axis에 투영한다.
// 중점사이의 벡터를 투영한 값과 각 스프라이트의 벡터를 투영한 값의 합을 비교하여 중점사이의 벡터가 길면 충돌 X, 스프라이트의 벡터 합이 크면 충돌하는 방식.
// 
bool Sprite::OBB(Sprite * b)
{
	return OBB(this, b);
}

bool Sprite::AABB(Sprite * a, D3DXVECTOR2 & position)
{
	float xScale = a->scale.x * a->TextureSize().x * 0.5f;
	float yScale = a->scale.y* a->TextureSize().y * 0.5f;

	float left = a->position.x - xScale;
	float right = a->position.x + xScale;
	float bottom = a->position.y - yScale;
	float top = a->position.y + yScale;

	// position이 Sprite와 겹치는 영역이 있는지 검사 => Sprite 내부에 있는지 검사함
	bool b = true;
	b &= position.x > left;
	b &= position.x <= right;
	b &= position.y > bottom;
	b &= position.y <= top;

	return b;
}

bool Sprite::AABB(Sprite * a, Sprite * b)
{
	float xScale = a->scale.x * a->TextureSize().x * 0.5f;
	float yScale = a->scale.y* a->TextureSize().y * 0.5f;

	float leftA   = a->position.x - xScale;
	float rightA  = a->position.x + xScale;
	float bottomA = a->position.y - yScale;
	float topA    = a->position.y + yScale;

	xScale = b->scale.x * b->TextureSize().x * 0.5f;
	yScale = b->scale.y * b->TextureSize().y * 0.5f;

	float leftB = b->position.x - xScale;
	float rightB = b->position.x + xScale;
	float bottomB = b->position.y - yScale;
	float topB = b->position.y + yScale;
	   	 	

	bool bCheck = true;
	bCheck &= leftB < rightB;
	bCheck &= topA > bottomB;
	bCheck &= rightA > leftB;
	bCheck &= bottomA < topB;

	return bCheck;
}

bool Sprite::OBB(Sprite * a, Sprite * b)
{
	OBBDesc obbA, obbB;
	float xScale, yScale;

	// _11, _22 : xscale, yscale, sprite a의 길이 구함
	D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22) * 0.5f;

	// OBB 생성
	CreateOBB(&obbA, a->position, a->world, lengthA);

	// _11, _22 : xscale, yscale, sprite b의 길이 구함
	D3DXVECTOR2 lengthB = D3DXVECTOR2(b->world._11, b->world._22) * 0.5f;

	// obb 생성
	CreateOBB(&obbB, b->position, b->world, lengthB);

	// 생성된 obb값으로 check
	return CheckOBB(obbA, obbB);
}

// obbDesc 생성하는 메소드, out을 출력 매개변수로 받고, position, world, length를 이용한다.
void Sprite::CreateOBB(OUT OBBDesc * out, D3DXVECTOR2 & position, D3DXMATRIX & world, D3DXVECTOR2 & length)
{
	// obbDesc.position에 position 입력
	out->Position = position;
	// obbDesc.length에 length 입력
	out->Length[0] = length.x;
	out->Length[1] = length.y;
	// obbDesc.direction에 world.11/12,. 21/22 입력
	out->Direction[0] = D3DXVECTOR2(world._11, world._12);
	out->Direction[1] = D3DXVECTOR2(world._21, world._22);

	// directon을 정규화. => seperate axis
	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);

}

// seperate axis에 두 벡터를 내적한 값의 절대값을 합한 값을 반환.
float Sprite::SeperateAxis(D3DXVECTOR2 seperate, D3DXVECTOR2 & e1, D3DXVECTOR2 & e2)
{
	// fabsf : 절대값. dxdxvec2dot : 내적
	float r1 = fabsf(D3DXVec2Dot(&seperate, &e1));
	float r2 = fabsf(D3DXVec2Dot(&seperate, &e2));

	return r1 + r2;
}

bool Sprite::CheckOBB(OBBDesc & obbA, OBBDesc & obbB)
{
	// nea : A의 seperate Axis, ea : A의 seperate axis * length
	D3DXVECTOR2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];
	D3DXVECTOR2 nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];
	// neb : B의 seperate Axis, eb : B의 seperate axis * length
	D3DXVECTOR2 neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];
	D3DXVECTOR2 neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];

	D3DXVECTOR2 direction = obbA.Position - obbB.Position; // 중점 사이의 벡터


	float lengthA = 0.0f, lengthB = 0.0f, length = 0.0f;

	// lengthA : ea1의 길이
	lengthA = D3DXVec2Length(&ea1);
	// lengthB : nea1로 spriteB의 길이 eb1, eb2 투영
	lengthB = SeperateAxis(nea1, eb1, eb2);
	// 중점사이의 길이를 nea1로 투영한 값
	length = fabsf(D3DXVec2Dot(&direction, &nea1));
	// 중점 사이의 길이가 각 스프라이트의 길이의 합보다 크면 해당 축에서는 충돌 X, 작으면 해당 축에서 충돌.
	if (length > lengthA + lengthB)
		return false;

	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeperateAxis(nea2, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea2));
	if (length > lengthA + lengthB)
		return false;


	lengthA = SeperateAxis(neb1, ea1, ea2);
	lengthB = D3DXVec2Length(&eb1);
	length = fabsf(D3DXVec2Dot(&direction, &neb1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = SeperateAxis(neb2, ea1, ea2);
	lengthB = D3DXVec2Length(&eb2);
	length = fabsf(D3DXVec2Dot(&direction, &neb2));
	if (length > lengthA + lengthB)
		return false;

	return true;	
}

//-----------------------------------------------------------------------------
//Sprites
//-----------------------------------------------------------------------------
map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	if (spriteMap.count(file) > 0)
	{
		spriteMap[file].RefCount++;

		return spriteMap[file].SRV;
	}

	HRESULT hr;
	ID3D11ShaderResourceView* srv;
	hr = D3DX11CreateShaderResourceViewFromFile(Device, file.c_str(), NULL, NULL, &srv, NULL);
	assert(SUCCEEDED(hr));

	SpriteDesc desc;
	desc.RefCount++;
	desc.SRV = srv;
	spriteMap[file] = desc;

	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	UINT count = spriteMap.count(file);
	assert(count > 0);

	spriteMap[file].RefCount--;
	if (spriteMap[file].RefCount < 1)
	{
		SAFE_RELEASE(spriteMap[file].SRV);

		spriteMap.erase(file);
	}
}
