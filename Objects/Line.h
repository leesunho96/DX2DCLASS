#pragma once

class Marker;
class Sprite;
class Line
{
public:
	Line(Marker* a, Marker* b);
	~Line();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	bool CollisionTest(Sprite* input);
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
	BoundVertex pastVertices[2];

	float slope = 0.0f;

	// shader
	Shader* boundShader;
	ID3D11Buffer* boundVertexBuffer;
	D3DXVECTOR2 normalVector = D3DXVECTOR2(0, 0);
	bool bistouch = false;
	D3DXVECTOR3 lineEquation = D3DXVECTOR3(0, 0, 0);

private:
	float GetSlope();
	D3DXVECTOR3 GetLineEquastion();
	float GetDistanceBetweenLineAndPoint(D3DXVECTOR3 line, D3DXVECTOR2 point);
	bool IsCollide(Sprite* input);
	bool IsInAreaX(D3DXVECTOR2 pos);
	bool IsInAreaY(D3DXVECTOR2 pos);

};