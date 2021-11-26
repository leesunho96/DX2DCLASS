#pragma once

#include "Scene.h"

class Player;
class Bullet;
class Fire;

class Stage2 : public Scene
{
public:
	Stage2(SceneValues* values);
	~Stage2();

	void Update() override;
	void Render() override;

private:
	void RenderBackground();
		
private:
	Sprite* backGrounds[3];

	Player* player;
	Bullet* bullet;
	Fire* fire;

	bool check;
};