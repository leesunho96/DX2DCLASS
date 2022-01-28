#pragma once

class SceneValues;
class Line;
class Marker;
class Player;
class CollisionData;
class CollisionDesc;


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
	D3DXVECTOR2 GetGoBackVector(Sprite* sprite);

	void SetCollisionDesc(CollisionDesc& collisiondesc);
	// 해당 충돌 시스템을 위한 선/좌표 입력 메소드.
	void PushMarkerByCode(D3DXVECTOR2 Point);
	void PushLineByCode(Line* line);
	void PushLineByCode(vector<Line*> line);
	void GetCollisionData(CollisionData* data);
	//void PushCollisionSettingByDesc(LineDesc& desc); // 라인과 마커 별개로 인식.
	void GetInArea(Sprite* sprite);
	// 기존에 입력된 충돌 좌표/선 초기화 메소드
	void ClearMarkersAndLines();

	vector<float> GetDistance(Sprite* input);

	bool GetIsOnUpperLine(Sprite* sprite);
	bool GetIsOnUpperLine(D3DXVECTOR2 point);

private:
	vector<bool>& GetDistanceBetweenLineAndZeroPosition(vector<Line*> lines);
private:
	void Update();
	D3DXVECTOR2 mpos;
	//vector<Marker*> markers;
	//vector<Line*> lines;
	SceneValues* scenevalue;
	Player* player;
	vector<int> CollideLineIndexVector;
	bool bIsRenderMarker = true;
	vector<bool> bDistanceIsPositive;
	vector<CollisionDesc> collisionDesc;

private:
	CollisionData* collisiondata;
};