#pragma once

class Ball
{
public:
	Ball(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	void InitializeVelocityPosition(const D3DXVECTOR2 &start, float angle, float speed);
	~Ball();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	D3DXVECTOR2 GetPosition() { return position; };
	Sprite* GetSprite() { return sprite; };

	void CollisionTestWithBall(Sprite * others);
	void CollisionTestWithPlayer(Sprite * player);

private:
	D3DXVECTOR2 velocity;
	Sprite* sprite;

	const D3DXVECTOR2 startPosition;
	const float speed;
	const float angle;

	float presentSpeed = speed;

	D3DXVECTOR2 position;	

	static vector<Ball*> ballVector;

private:
	void CollisionTest();
	void testMethod();
	int CheckOverlapWall();

	bool IsOnTop();
	bool IsOnBottom();
	bool IsOnLeft();
	bool IsOnRight();

	void OverlapTop();
	void OverlapDieSection();
	void OverlapLeft();
	void OverlapRight();
	void OverlapOthersBottom();

	void setStop();
	D3DXVECTOR2 GetReflectionVector(D3DXVECTOR2 v2n);
};