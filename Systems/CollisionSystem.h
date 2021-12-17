#pragma once

class SceneValues;
//class Scene;
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
	bool CollisionTest(Sprite* sprite);
	float GetDegree(Sprite* sprite);

	void PushMarkerByCode(D3DXVECTOR2 Point);

	vector<float> GetDistance(Sprite* input);

	bool GetIsOnUpperLine(Sprite* sprite);
	bool GetIsOnUpperLine(D3DXVECTOR2 point);

private:
	D3DXVECTOR2 mpos;
	vector<Marker*> markers;
	vector<Line*> lines;
	SceneValues* scenevalue;
	Player* player;
	vector<int> CollideLineIndexVector;
	bool bIsRenderMarker = true;
private:

};