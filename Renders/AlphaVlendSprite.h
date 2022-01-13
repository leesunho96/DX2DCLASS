#pragma once

class AlphaBlendSprite
{
public:
	AlphaBlendSprite(wstring textureFile, wstring shaderFile);
	AlphaBlendSprite(wstring texturefile, wstring shaderFile, float endX, float endY);
	AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	virtual ~AlphaBlendSprite();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void DrawBound(bool val) { bDrawBound = val; }
	void DrawCollision(bool val) { bDrawCollision = val; }



public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);

	void SetAbsoluteScale(float x, float y);
	void SetAbsoluteScale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize() { return textureSize; }

	D3DXMATRIX GetWorld() { return world; };
	void SetAlphaBlendValues(float input) { fAlphaBlendValues = input; }

public:
	// axis aligned bounding boxes
	// 축이 정렬된 객체들의 충돌

	bool AABB(D3DXVECTOR2 position);
	bool AABB(AlphaBlendSprite* b);

	bool OBB(AlphaBlendSprite* b);
	bool OBB(RECT rect);
	
	static bool AABB(AlphaBlendSprite* a, D3DXVECTOR2& position);
	static bool AABB(AlphaBlendSprite* a, AlphaBlendSprite* b);

	static bool OBB(AlphaBlendSprite* a, AlphaBlendSprite* b);

	// 충돌 구현 위한 bound
	// 충돌은 각 스프라이트에서 일어나야 함. 스프라이트 크기 변경시 충돌 반경도 변해야 함.

private:
	struct OBBDesc
	{
		D3DXVECTOR2 Position;
		D3DXVECTOR2 Direction[2];
		float Length[2];
	};

	static void CreateOBB(OUT OBBDesc* out, D3DXVECTOR2& position, D3DXMATRIX& world, D3DXVECTOR2& length);
	static float SeperateAxis(D3DXVECTOR2 seperate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckOBB(OBBDesc& obbA, OBBDesc& obbB);
private:
	void CreateBound();


private:
	void Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	//void UpdateWorld();


private:
	wstring textureFile;

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	// 충돌 위한 셰이더
	Shader* boundShader;
	ID3D11Buffer* boundVertexBuffer;
	bool bDrawBound;
	bool bDrawCollision;

	bool bIsValidate = false;
	float fAlphaBlendValues = 0.0f;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 textureSize;
	D3DXMATRIX world;
	ID3D11ShaderResourceView* srv;
	
private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

	struct BoundVertex
	{
		D3DXVECTOR3 Position;

	};
};

///////////////////////////////////////////////////////////////////////////////

class AlphaBlendSprites
{
private:
	friend class AlphaBlendSprite;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};

	static map<wstring, SpriteDesc> spriteMap;
};
