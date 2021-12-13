#pragma once

class SceneValues;
class Line;
class Marker;

class CollisionSystem
{
public:
	CollisionSystem(SceneValues * values);
	~CollisionSystem();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void CollisionTest(Sprite* sprite);

private:
	D3DXVECTOR2 mpos;
	vector<Marker*> markers;
	vector<Line*> lines;
	SceneValues* scenevalue;
};