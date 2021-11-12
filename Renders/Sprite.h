#pragma once

class Sprite
{

public:
	// ���� ������ �����ε�. �⺻������ ��½�ų ��������Ʈ, ���̴� ���� �䱸��.
	// �߰������� ��������Ʈ�� �ϳ��� �̹����� ��� 
	//startX, startY : 0
	//endX, endY : 1�� �� ���̴�.
	// �׷��� �ʰ� �������� �̹����� ���� �ִ� ��������Ʈ�� ��� �ش� ���� �����Ͽ�
	//���ϴ� ������ �̹��� ���.
	// �Ű������� �������� �ʴ°�� ����Ʈ�� 0�� ����ִ´� 
	// => �� �Է� ���� ������ ȭ�鿡 ��� ���� ����.
	Sprite(wstring textureFile, wstring shaderFile);

	Sprite(wstring textureFile, wstring shaderFile, 
		float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, 
		float startX, float startY, 
		float endX, float endY);
	// �ش� ��ü �Ҹ���.
	virtual ~Sprite();
	//�ش� ��ü�� WVP��  ������ ���� �޼ҵ�


	// Update �޼ҵ�
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	// Render �޼ҵ�
	void Render();

public:
	// ��ü�� ���� ��ǥ�� ���� �޼ҵ�
	void Position(float x, float y);
	void Position(D3DXVECTOR2& position);
	// ��ü�� ���� ��ǥ�� ��ȯ �޼ҵ�
	D3DXVECTOR2 Position();

	// ��ü�� ũ�� ���� �޼ҵ�. 
	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& scale);
	// ��ü�� ũ�� ��ȯ �޼ҵ�
	D3DXVECTOR2 Scale();

	// ��ü�� �ؽ��� ũ�� ��ȯ �޼ҵ�.
	D3DXVECTOR2 TextureSize() { return textureSize; };
private:
	// �����ڿ��� �������� ��� �� �ʱ�ȭ �޼ҵ�. �ش� �޼ҵ忡 ������ �� �Է��Ͽ�
	// ������ ����
	void Initialize(wstring spriteFile, wstring shaderFile,
		float startX, float startY,
		float endX, float endY);
	void UpdateWorld();
private:
	// ��������Ʈ�� �� ���� �޼ҵ�.
	// �ش� ������ �� ������ ��ġ�� �ش� �޼ҵ�� ��Ī�� ��������Ʈ�� ��ǥ ����.
	// png������ ��� y���� ������ dx3d�� �ݴ���. ���� y�� �ݴ�� ���� �� �ʿ� ����.
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
// ��������Ʈ ��� ���� Ŭ����
class Sprites
{
private:
	// Sprite�� friend �����Ͽ� Sprite���� �ش� ���� �޼ҵ� ���� ����.
	friend class Sprite; // Sprite������ ���� ����.
private:
	// �ش� Ŭ�������� file�� �����ϴ� �� Ȯ���ϰ� �����ϸ� �ش� srv ��ȯ, 
	//�������� ������ srv �����ؼ� ��ȯ, ref counter �� ����.
	static ID3D11ShaderResourceView* Load(wstring file);
	// �ش� ������ spriteDesc ����.
	static void Remove(wstring file);
private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};
	static map<wstring, SpriteDesc> spriteMap;
};