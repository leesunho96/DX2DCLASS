#pragma once

class SceneValues;
class Line;
class Marker;
class Player;
class CollisionData;



class CollisionSystem
{
public:
	CollisionSystem(SceneValues * values, Player* player);
	~CollisionSystem();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	bool CollisionTest(Sprite* sprite);
	bool CollisionTest(RECT spritestatus);
	float GetDegree(Sprite* sprite);


	// �ش� �浹 �ý����� ���� ��/��ǥ �Է� �޼ҵ�.
	void PushMarkerByCode(D3DXVECTOR2 Point);
	void PushLineByCode(Line* line);
	void PushLineByCode(vector<Line*> line);
	void GetCollisionData(CollisionData* data);
	//void PushCollisionSettingByDesc(LineDesc& desc); // ���ΰ� ��Ŀ ������ �ν�.

	// ������ �Էµ� �浹 ��ǥ/�� �ʱ�ȭ �޼ҵ�
	void ClearMarkersAndLines();

	vector<float> GetDistance(Sprite* input);

	bool GetIsOnUpperLine(Sprite* sprite);
	bool GetIsOnUpperLine(D3DXVECTOR2 point);

private:
	D3DXVECTOR2 mpos;
	//vector<Marker*> markers;
	//vector<Line*> lines;
	SceneValues* scenevalue;
	Player* player;
	vector<int> CollideLineIndexVector;
	bool bIsRenderMarker = true;
private:
	CollisionData* collisiondata;
};