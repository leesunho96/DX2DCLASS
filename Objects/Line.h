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

	// 스프라이트 획득 이후. 해당 스프라이트와 충돌하는지 체크.
	// 충돌 방식은 스프라이트 네 꼭지점과 선 사이의 거리를 잰 후, 해당 값 중 0이 있거나 모두 양수가 아니거나 모두 음수가 아닌경우 충돌로 체크.
	bool CollisionTest(Sprite* input);

	// 스프라이트와 해당 라인 사이의 각도 반환.
	float GetAngle() { return angle; };

	// 해당 선과 각 스프라이트/좌표 사이의 거리.
	float GetDistance(Sprite* sprite);
	float GetDistance(D3DXVECTOR2 point);

	// line의 marker 획득을 위한 메소드.
	pair<Marker*, Marker*> GetMarker() { return make_pair(startpos, endPos); };
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