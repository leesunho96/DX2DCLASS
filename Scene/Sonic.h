#pragma once

#include "Scene.h"

class Player;
//class Marker;

class Sonic : public Scene
{
public:
	Sonic(SceneValues* values);
	~Sonic();

	void Update() override;
	void Render() override;
private:
	Sprite* backGround;
	Player* player;
	//vector<Marker*> markers;
};