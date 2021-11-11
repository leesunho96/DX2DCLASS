#pragma once

class Rect
{
public:
	Rect(wstring shaderFile, wstring imgFile);
	Rect(wstring shaderFile, wstring imgFile, 
		D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Rect();

	void ViewProjection(D3DXMATRIX& V, D3DXMATRIX& P);

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }
	RECT GetWorldLocation();

private:
	void CreateBuffer(wstring shaderFile, wstring imgFile);
	void UpdateWorld();

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};
private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;
	ID3D11ShaderResourceView* srv;


	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXMATRIX W, S, T;
	Vertex vertices[6];

};