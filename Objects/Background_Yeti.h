#pragma once

class Sprite;
class LineDesc;
class SceneValues;
class Line;
class CollisionData;


class Background_Yeti
{
public:
	Background_Yeti(SceneValues* scenevalues, float Scale);
	~Background_Yeti();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	
	CollisionData* GetCollisionData() { return collisiondata; };

private:
	Sprite* mapSprite;	
	CollisionData* collisiondata;	
};