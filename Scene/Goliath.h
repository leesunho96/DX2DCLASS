#pragma once

#include "Scene.h"


class Player;
class CollisionSystem;
class ActorsData;
class Yeti;
class UI;
class Background_Goliath
extern bool bIsDebugging;

class Goliath : public Scene
{
public:
	Goliath(SceneValues* values);
	~Goliath();

	void Update() override;
	void Render() override;

	void ChangeCamera();

private:
	Background_Goliath* bg;
	Player* player;
	Yeti* yeti;
	//
	UI* ui;
	// for debugging
	bool check;
};