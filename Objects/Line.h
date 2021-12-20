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

	// ��������Ʈ ȹ�� ����. �ش� ��������Ʈ�� �浹�ϴ��� üũ.
	// �浹 ����� ��������Ʈ �� �������� �� ������ �Ÿ��� �� ��, �ش� �� �� 0�� �ְų� ��� ����� �ƴϰų� ��� ������ �ƴѰ�� �浹�� üũ.
	bool CollisionTest(Sprite* input);

	// ��������Ʈ�� �ش� ���� ������ ���� ��ȯ.
	float GetAngle() { return angle; };

	// �ش� ���� �� ��������Ʈ/��ǥ ������ �Ÿ�.
	float GetDistance(Sprite* sprite);
	float GetDistance(D3DXVECTOR2 point);

	// line�� marker ȹ���� ���� �޼ҵ�.
	pair<Marker*, Marker*> GetMarker() { return make_pair(startpos, endPos); };
private:
	struct BoundVertex
	{
		D3DXVECTOR3 Position;
	};
private:
	// ���� ����/�� marker
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
	float angle = 0.0f;
private:
	struct SpriteStatus
	{
		D3DXVECTOR2 rightUp;
		D3DXVECTOR2 rightDown;
		D3DXVECTOR2 leftUp;
		D3DXVECTOR2 leftDown;
	};

private:
	float GetDegree();
	float GetSlope();
	D3DXVECTOR3 GetLineEquastion();
	float GetDistanceBetweenLineAndPoint(D3DXVECTOR3 line, D3DXVECTOR2 point);
	bool IsCollide(Sprite* input);
	bool IsInAreaX(D3DXVECTOR2 pos);
	bool IsInAreaY(D3DXVECTOR2 pos);

	bool IsLinePointInSpriteWidth(SpriteStatus spritestatus);
	bool IsLinePointInSpriteHeight(SpriteStatus spritestatus);

	bool IsInArea(SpriteStatus input);


};