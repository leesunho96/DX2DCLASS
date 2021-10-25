#pragma once
class myRectDraw
{
	ID3D11Buffer* vertexBuffer;
	Vertex vertices[6];
	D3DXMATRIX W, V, P;
	D3DXMATRIX S, R, T;
	Shader* shader;
	D3DXVECTOR2 position;

public:
	myRectDraw();
	void setPosition(D3DXVECTOR2 Position);
	void Update();
	void Render();
	~myRectDraw();
};

