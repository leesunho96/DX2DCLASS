#pragma once

class Line;

class Collision
{
public:
	Collision();
	~Collision();

	void SetCollision(D3DXVECTOR2 points);
	void DeleteCollision();
private:
public:
private:
	Line* line[4];

};