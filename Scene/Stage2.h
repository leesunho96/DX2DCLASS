#pragma once

#include "Scene.h"

class Background_Yeti;
class Player;
class CollisionSystem;
class Icycle;

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

	Icycle* icycle;
	bool check;
};