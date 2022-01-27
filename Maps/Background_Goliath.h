#pragma once

class Sprite;
class LineDesc;
class SceneValues;
class Line;
class CollisionData;

class Background_Goliath
{
public:
	Background_Goliath(SceneValues* scenevalues, float Scale);
	~Background_Goliath();

	CollisionData* GetCollisionData() { return collisiondata; };

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
public:
private:
	
	Sprite* mapSprite;
	CollisionData* collisiondata;
};