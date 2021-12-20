#pragma once

class SceneValues;
//class Scene;
class Line;
class Marker;
class Player;

struct LineDesc
{
	vector<Line*> lines;
	vector<Marker*> Markers;
};

class CollisionSystem
{
public:
	CollisionSystem(SceneValues * values, Player* player);
	~CollisionSystem();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	bool CollisionTest(Sprite* sprite);
	float GetDegree(Sprite* sprite);


	// �ش� �浹 �ý����� ���� ��/��ǥ �Է� �޼ҵ�.
	void PushMarkerByCode(D3DXVECTOR2 Point);
	void PushLineByCode(Line* line);
	void PushCollisionSettingByDesc(LineDesc& desc); // ���ΰ� ��Ŀ ������ �ν�.

	// ������ �Էµ� �浹 ��ǥ/�� �ʱ�ȭ �޼ҵ�
	void ClearMarkersAndLines();

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