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

	D3DXVECTOR2 vPosition; // ȭ�� ��ü ���� ��ġ
	D3DXVECTOR2 vRadius; // ȭ���� ����ų ���� ���� => bullet�� ���� ����

	float fangle = 0.0f;
	const D3DXVECTOR2 baseBulletPosition = D3DXVECTOR2(Width / 2, 30);
};