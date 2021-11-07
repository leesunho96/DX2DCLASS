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
	// 매개변수로 입력받은 스프라이트 파일을 클래스 내의 텍스쳐 파일에 저장.
	textureFile = spriteFile;

	// 셰이더 생성
	shader = new Shader(shaderFile);
	// Sprite 제어용 클래스 Sprites에서 spriteFile 불러옴.
	// 해당 메소드는 static으로 선언된 Map에 저장 되어있는 SpriteDesc 체크 후, 
	// 해당 값반환. 만약 이전에 생성 된 적이 없으면 생성 이후 반환.
	srv = Sprites::Load(spriteFile);
	// shader의 Texture2D인 Map에 srv를 전달.
	shader->AsShaderResource("Map")->SetResource(srv);

	// 화면에 출력될 위치는 0, 0 , 크기는 1,1 선언
	Position(0, 0);
	Scale(1, 1);

	HRESULT hr;
	// 출력할 이미지의 정보를 갖는 info 구조체 선언.
	D3DX11_IMAGE_INFO info;

	// 파일로 저장된 이미지를 불러오고, 해당 관련 값을 info에 저장한다.
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL);
	assert(SUCCEEDED(hr));

	// 각 스프라이트의 시작 X, Y 좌표를 얻는 식.
	// startX, Y가 0보다 크면 X, Y를  이미지의 width/height로 나눈값 저장.
	// 0보다 작거나 같으면 (예외사항) 0을 저장.
	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	// startX, Y와 동일. 다만 end이기 때문에 아닌 경우 1.0 저장.
	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	// 각 정점들 저장.
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



	// endX가 0보다 크면 sizeX = endX * info.width =>0부터 sprite의 끝까지의 길이
	float sizeX = (endX > 0) ? 
		endX * (float)info.Width 
		: (float)info.Width;
	// 실제 스프라이트 크기 구하는 식. 
	//sizeX는 0부터 sprite의 endX까지 길이였는데 거기서 
	// 0부터 startX까지의 길이를 빼면 실제 스프라이트 길이가 나옴.
	sizeX -= startX * (float)info.Width;

	// 위와 동일
	float sizeY = (endY > 0) ? 
		endY * (float)info.Height 
		: (float)info.Height;
	sizeY -= startY * (float)info.Height;

	// 실제 출력할 크기.
	scale = D3DXVECTOR2(sizeX, sizeY);

	UpdateWorld();

	// vertexBUffer생성.
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
	// 해당 V, P shader에 넘겨줌.
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

	// 원시도형 triangleLIst로 설정 후, vertex 0~5까지 그림.
	// pass는 0번.
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);
}

void Sprite::Position(float x, float y)
{
	// 화면에 그릴 위치 설정 메소드.
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
	// 스프라이트 스케일 변경 메소드
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
	// W = SRT // Scale(크기) Rotation(회전) Translation(평행이동)
	shader->AsMatrix("World")->SetMatrix(W);
}


//-----------------------------------------------------------------------------
//Sprites
//-----------------------------------------------------------------------------
// static Map이라 외부에서 초기화 필요.
map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	//해당 맵의 카운트가 0이면 => 이전에 생성 한적이 없거나
	// 생성 한 이후, 다시 해제함.
	// 해당 맵 카운트가 0이상이라면 이미 생성 한 적이 있고, 해당 SRV를 갖고 있음
	if (spriteMap.count(file) > 0)
	{
		// 해당 맵의 refcoumt ++
		spriteMap[file].RefCount++;
		// 해당 맵 srv 반환
		return spriteMap[file].SRV;
	}

	// spriteMap의 refcount가 0이면 이전에 생성 한 적이 없기 때문에 해당
	// SRV 생성이 필요함.
	HRESULT hr;
	ID3D11ShaderResourceView* srv;

	/*hr = */
	D3DX11CreateShaderResourceViewFromFile
	(
		Device,			// *pDevice 해당 리소스를 사용하는 장치에 대한 포인터
		file.c_str(),	//pSrcFile, LPCTSTR타입이라 c_str()로 반환. 셰이더 리소스 뷰를 포함하는 파일 이름.
		NULL,			// *PLoadInfo 셰이더의 texture 특성 식별, 해당 로드시 질감 특성 읽으려면 NULL
		NULL,			//*pPump 스레드펌프인터페이스 포인터. NULL선언시 동기적으로 동작, 완료시까지 반환되지 않음.
		&srv,			//**ppShaderResourceView SRV의 값. 해당 값에 저장. 
		&hr				// *pHResult HRESULT 값 
	); 
	assert(SUCCEEDED(hr));

	SpriteDesc desc; // Sprite의 refcnt, srv저장하고 있는 Sprites내부에 선언된 구조체.
	desc.RefCount++;
	desc.SRV = srv;
	spriteMap[file] = desc;

	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	// spriteMap이 없는데 삭제 시도시 오류 발생하기 때문에 해당 과정 거침.
	// count<=0이면 해당 구문 오류 반환
	UINT count = spriteMap.count(file);
	assert(count > 0);
	//refcnt 감소시키고, 0이 되면 해당 spriteDesc 해제.
	spriteMap[file].RefCount--;
	if (spriteMap[file].RefCount < 1)
	{
		SAFE_RELEASE(spriteMap[file].SRV);

		spriteMap.erase(file);
	}
}
