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
	// �Ű������� �Է¹��� ��������Ʈ ������ Ŭ���� ���� �ؽ��� ���Ͽ� ����.
	textureFile = spriteFile;

	// ���̴� ����
	shader = new Shader(shaderFile);
	// Sprite ����� Ŭ���� Sprites���� spriteFile �ҷ���.
	// �ش� �޼ҵ�� static���� ����� Map�� ���� �Ǿ��ִ� SpriteDesc üũ ��, 
	// �ش� ����ȯ. ���� ������ ���� �� ���� ������ ���� ���� ��ȯ.
	srv = Sprites::Load(spriteFile);
	// shader�� Texture2D�� Map�� srv�� ����.
	shader->AsShaderResource("Map")->SetResource(srv);

	// ȭ�鿡 ��µ� ��ġ�� 0, 0 , ũ��� 1,1 ����
	Position(0, 0);
	Scale(1, 1);

	HRESULT hr;
	// ����� �̹����� ������ ���� info ����ü ����.
	D3DX11_IMAGE_INFO info;

	// ���Ϸ� ����� �̹����� �ҷ�����, �ش� ���� ���� info�� �����Ѵ�.
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL);
	assert(SUCCEEDED(hr));

	// �� ��������Ʈ�� ���� X, Y ��ǥ�� ��� ��.
	// startX, Y�� 0���� ũ�� X, Y��  �̹����� width/height�� ������ ����.
	// 0���� �۰ų� ������ (���ܻ���) 0�� ����.
	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	// startX, Y�� ����. �ٸ� end�̱� ������ �ƴ� ��� 1.0 ����.
	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	// �� ������ ����.
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



	// endX�� 0���� ũ�� sizeX = endX * info.width =>0���� sprite�� �������� ����
	float sizeX = (endX > 0) ? 
		endX * (float)info.Width 
		: (float)info.Width;
	// ���� ��������Ʈ ũ�� ���ϴ� ��. 
	//sizeX�� 0���� sprite�� endX���� ���̿��µ� �ű⼭ 
	// 0���� startX������ ���̸� ���� ���� ��������Ʈ ���̰� ����.
	sizeX -= startX * (float)info.Width;

	// ���� ����
	float sizeY = (endY > 0) ? 
		endY * (float)info.Height 
		: (float)info.Height;
	sizeY -= startY * (float)info.Height;

	// ���� ����� ũ��.
	scale = D3DXVECTOR2(sizeX, sizeY);

	UpdateWorld();

	// vertexBUffer����.
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

}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);

	Sprites::Remove(textureFile);
}



void Sprite::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	// �ش� V, P shader�� �Ѱ���.
 	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	WorldPosition.left = (float)((position.x) - (scale.x / 2));
	WorldPosition.top = (float)((position.y) - (scale.y / 2));
	WorldPosition.right = (float)((position.x) + (scale.x / 2));
	WorldPosition.bottom = (float)((position.y) + (scale.y / 2));


}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// ���õ��� triangleLIst�� ���� ��, vertex 0~5���� �׸�.
	// pass�� 0��.
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);
}

void Sprite::Position(float x, float y)
{
	// ȭ�鿡 �׸� ��ġ ���� �޼ҵ�.
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 &vec)
{
	position = vec;

	UpdateWorld();
}

D3DXVECTOR2 Sprite::Position()
{
	return position;
}

void Sprite::Scale(float x, float y)
{
	// ��������Ʈ ������ ���� �޼ҵ�
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale.x *= vec.x;
	scale.y *= vec.y;

	UpdateWorld();
}

D3DXVECTOR2 Sprite::Scale()
{
	return scale;
}

RECT Sprite::GetRect()
{
	return WorldPosition;
}

void Sprite::Rotation(float radius)
{
	this->radius = Math::ToRadian(radius);
}

float Sprite::Rotation()
{
	return radius;
}


void Sprite::UpdateWorld()
{
	D3DXMATRIX W, S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	D3DXMatrixRotationAxis(&R, &D3DXVECTOR3(0, 0, 1), radius);
	W = S * R * T;
	// W = SRT // Scale(ũ��) Rotation(ȸ��) Translation(�����̵�)
	shader->AsMatrix("World")->SetMatrix(W);
}


//-----------------------------------------------------------------------------
//Sprites
//-----------------------------------------------------------------------------
// static Map�̶� �ܺο��� �ʱ�ȭ �ʿ�.
map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	//�ش� ���� ī��Ʈ�� 0�̸� => ������ ���� ������ ���ų�
	// ���� �� ����, �ٽ� ������.
	// �ش� �� ī��Ʈ�� 0�̻��̶�� �̹� ���� �� ���� �ְ�, �ش� SRV�� ���� ����
	if (spriteMap.count(file) > 0)
	{
		// �ش� ���� refcoumt ++
		spriteMap[file].RefCount++;
		// �ش� �� srv ��ȯ
		return spriteMap[file].SRV;
	}

	// spriteMap�� refcount�� 0�̸� ������ ���� �� ���� ���� ������ �ش�
	// SRV ������ �ʿ���.
	HRESULT hr;
	ID3D11ShaderResourceView* srv;

	/*hr = */
	D3DX11CreateShaderResourceViewFromFile
	(
		Device,			// *pDevice �ش� ���ҽ��� ����ϴ� ��ġ�� ���� ������
		file.c_str(),	//pSrcFile, LPCTSTRŸ���̶� c_str()�� ��ȯ. ���̴� ���ҽ� �並 �����ϴ� ���� �̸�.
		NULL,			// *PLoadInfo ���̴��� texture Ư�� �ĺ�, �ش� �ε�� ���� Ư�� �������� NULL
		NULL,			//*pPump �����������������̽� ������. NULL����� ���������� ����, �Ϸ�ñ��� ��ȯ���� ����.
		&srv,			//**ppShaderResourceView SRV�� ��. �ش� ���� ����. 
		&hr				// *pHResult HRESULT �� 
	); 
	assert(SUCCEEDED(hr));

	SpriteDesc desc; // Sprite�� refcnt, srv�����ϰ� �ִ� Sprites���ο� ����� ����ü.
	desc.RefCount++;
	desc.SRV = srv;
	spriteMap[file] = desc;

	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	// spriteMap�� ���µ� ���� �õ��� ���� �߻��ϱ� ������ �ش� ���� ��ħ.
	// count<=0�̸� �ش� ���� ���� ��ȯ
	UINT count = spriteMap.count(file);
	assert(count > 0);
	//refcnt ���ҽ�Ű��, 0�� �Ǹ� �ش� spriteDesc ����.
	spriteMap[file].RefCount--;
	if (spriteMap[file].RefCount < 1)
	{
		SAFE_RELEASE(spriteMap[file].SRV);

		spriteMap.erase(file);
	}
}
