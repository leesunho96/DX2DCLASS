#pragma once

#include "Scene.h"

class Background_Yeti;
class Player;
class CollisionSystem;
class Icycle;
class SnowBall;

extern bool bIsDebugging;

class Stage2 : public Scene
{
public:
	Stage2(SceneValues* values);
	~Stage2();

	void Update() override;
	void Render() override;
	
private:
	Background_Yeti* bg;
	Player* player;
	//

	// for debugging

	Icycle* icycle;
	SnowBall* snowball;


	bool check;
};