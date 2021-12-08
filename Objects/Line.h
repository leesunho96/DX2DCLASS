#pragma once

class Marker;
class Scene;

extern SceneValues* values;

class Line
{
public:
	Line();
	~Line();


	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	vector<Marker*> activateMarker;
	vector<Marker*> MarkerPool;

	D3DXVECTOR2 mousePosition;
};


