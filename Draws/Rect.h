#pragma once

class Rect
{
public:
	Rect(wstring shaderFile);
	Rect(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	~Rect();

	void ViewProjection(D3DXMATRIX& V, D3DXMATRIX& P);

	void Update();
	void Render();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Color(float r, float g, float b);
	void Color(D3DXCOLOR& vec);
	D3DXCOLOR Color() { return color; }

	RECT GetWorldLocation();

private:
	void CreateBuffer(wstring shaderFile);
	void UpdateWorld();

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
	};
private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXCOLOR color;

	D3DXMATRIX W, S, T;
	Vertex vertices[6];

};