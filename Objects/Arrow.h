#pragma once

class Bullet;


class Arrow
{
private:
	void Initialize(wstring shaderFile, D3DXVECTOR2 start);
	D3DXVECTOR2 GetRadius(float angle);
	D3DXVECTOR2 GetBaseBulletLocation();
public:

	Arrow(wstring shaderFile, D3DXVECTOR2 start);
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	~Arrow();


private:
	Sprite* Arrows;

	D3DXVECTOR2 vPosition; // 화살 객체 생성 위치
	D3DXVECTOR2 vRadius; // 화살이 가리킬 벡터 방향 => bullet이 나갈 방향

	float fangle = 0.0f;
	const D3DXVECTOR2 baseBulletPosition = D3DXVECTOR2(Width / 2, 30);
};