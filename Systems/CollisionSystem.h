#pragma once

class SceneValues;
class Line;
class Marker;
class Player;

class CollisionSystem
{
public:
	CollisionSystem(SceneValues * values, Player* player);
	~CollisionSystem();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void CollisionTest(Sprite* sprite);
	float GetDegree(Sprite* sprite);
private:
	D3DXVECTOR2 mpos;
	vector<Marker*> markers;
	vector<Line*> lines;
	SceneValues* scenevalue;
	Player* player;
	bool bIsRenderMarker = true;
private:

};