#pragma once

class Sprite;
class LineDesc;
class SceneValues;
class Line;
class CollisionData;


class Background_Yeti
{
public:
	Background_Yeti(SceneValues* scenevalues);
	~Background_Yeti();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	//LineDesc GetCollision() { return mapCollision; };
	//vector<Line*> GetLineCollision() {
	//	return mapCollision.lines;
	//};
	vector<Line*> Getlines() { return lines; };
	CollisionData* GetCollisionData() { return collisiondata; };

private:
	Sprite* mapSprite;	
	CollisionData* collisiondata;
	vector<Line*> lines;
};