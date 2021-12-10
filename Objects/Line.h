#pragma once

class Marker;

class Line
{
public:
	Line(Marker* a, Marker* b);
	~Line();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	struct BoundVertex
	{
		D3DXVECTOR3 Position;
	};
private:
	// 각각 시작/끝 marker
	Marker* startpos;
	Marker* endPos;

	//vertex
	BoundVertex vertices[2];

	// shader
	Shader* boundShader;
	ID3D11Buffer* boundVertexBuffer;
	D3DXVECTOR2 normalVector = D3DXVECTOR2(0, 0);
	bool bistouch = false;
};