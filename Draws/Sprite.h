#pragma once

class Sprite
{

public:
	// 각각 생성자 오버로딩. 기본적으로 출력시킬 스프라이트, 셰이더 파일 요구함.
	// 추가적으로 스프라이트가 하나의 이미지인 경우 
	//startX, startY : 0
	//endX, endY : 1이 될 것이다.
	// 그렇지 않고 여러개의 이미지를 갖고 있는 스프라이트일 경우 해당 값을 조절하여
	//원하는 범위의 이미지 출력.
	// 매개변수로 삽입하지 않는경우 디폴트로 0을 집어넣는다 
	// => 값 입력 하지 않으면 화면에 출력 되지 않음.
	Sprite(wstring textureFile, wstring shaderFile);

	Sprite(wstring textureFile, wstring shaderFile, 
		float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, 
		float startX, float startY, 
		float endX, float endY);
	// 해당 객체 소멸자.
	virtual ~Sprite();
	//해당 객체의 WVP값  적용을 위한 메소드


	// Update 메소드
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	// Render 메소드
	void Render();

public:
	// 객체의 월드 좌표계 결정 메소드
	void Position(float x, float y);
	void Position(D3DXVECTOR2& position);
	// 객체의 월드 좌표계 반환 메소드
	D3DXVECTOR2 Position();

	// 객체의 크기 결정 메소드. 
	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& scale);
	// 객체의 크기 반환 메소드
	D3DXVECTOR2 Scale();

	// 객체의 텍스쳐 크기 반환 메소드.
	D3DXVECTOR2 TextureSize() { return textureSize; };
private:
	// 생성자에서 공통으로 사용 될 초기화 메소드. 해당 메소드에 적절한 값 입력하여
	// 생성자 구현
	void Initialize(wstring spriteFile, wstring shaderFile,
		float startX, float startY,
		float endX, float endY);
	void UpdateWorld();
private:
	// 스프라이트의 각 정점 메소드.
	// 해당 정점은 각 정점의 위치와 해당 메소드와 매칭될 스프라이트의 좌표 소유.
	// png파일의 경우 y축의 방향이 dx3d와 반대임. 따라서 y축 반대로 적용 할 필요 있음.
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

	wstring textureFile;
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 textureSize;

	ID3D11ShaderResourceView* srv;
public:
private:
public:

};


///////////////////////////////////////////////////////////////////////
// 스프라이트 제어를 위한 클래스
class Sprites
{
private:
	// Sprite를 friend 선언하여 Sprite에서 해당 제어 메소드 접근 가능.
	friend class Sprite; // Sprite에서는 접근 가능.
private:
	// 해당 클래스에서 file가 존재하는 지 확인하고 존재하면 해당 srv 반환, 
	//존재하지 않으면 srv 생성해서 반환, ref counter 값 수정.
	static ID3D11ShaderResourceView* Load(wstring file);
	// 해당 파일의 spriteDesc 삭제.
	static void Remove(wstring file);
private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};
	static map<wstring, SpriteDesc> spriteMap;
};