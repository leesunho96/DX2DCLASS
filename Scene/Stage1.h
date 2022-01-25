#pragma once

#include "Scene.h"


class Player;
class CollisionSystem;
class ActorsData;
class UI;
class Background_Goliath;
class Following;
class Goliath;

class Stage1 : public Scene
{
public:
	Stage1(SceneValues* values);
	~Stage1();

	void Update() override;
	void Render() override;

	void ChangeCamera();

private:
	Background_Goliath* bg;
	Player* player;
	Goliath* goliath;
	//
	UI* ui;
	Following* following;
	// for debugging
	bool check;
};