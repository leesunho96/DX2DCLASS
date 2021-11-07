#pragma once
class Arrow;

class Bullet
{
public:
	static vector<Bullet*> bulletVector;
public:
	void Initialize(std::wstring &shaderFile, const D3DXVECTOR2 &start);
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
	int getType() { return type; };
private:
	D3DXVECTOR2 velocity;
	Sprite* sprite;

	D3DXVECTOR2 position;
	bool isMoving = false;
	int type;
	void isOverlap(Bullet* past, Bullet* target);
	void AllocateBullet();
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