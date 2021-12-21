#pragma once

class Sprite;
class LineDesc;
class SceneValues;
class Line;


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
private:
	Sprite* mapSprite;	
	//LineDesc mapCollision;
	vector<Line*> lines;
};