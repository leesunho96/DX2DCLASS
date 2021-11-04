#pragma once

class Bullet
{
public:
	static vector<Bullet*> bulletvector;
public:
	Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	~Bullet();

	void Position(D3DXVECTOR2& pos);
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void setVelocity(float degree);
	RECT GetWorldPosition();
	bool getIsmoving();
	pair<int, int> getArrayList();
	D3DXVECTOR2 getVelocity();
	bool isGetRivision = false;
private:
	D3DXVECTOR2 velocity;
	Sprite* sprite;

	D3DXVECTOR2 position;
	bool isMoving = false;
	int type = 1;
	void isOverlap(Bullet* past, Bullet* target);
	void CollisionTest();
	void testMethod();
	int CheckOverlapWall();

	bool IsOnTop();
	bool IsOnBottom();
	bool IsOnLeft();
	bool IsOnRight();

	void OverlapTop();
	void OverlapBottom();
	void OverlapLeft();
	void OverlapRight();

	void setStop();
	D3DXVECTOR2 GetReflectionVector(D3DXVECTOR2 v2n);

};