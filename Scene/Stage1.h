#pragma once

#include "Scene/Scene.h"

// cpp에는 헤더 존재하지만 해당 파일에는 존재하지 않음. 따라서 선언되었음을 알려주기 위해 전방선언
class Player;
class Bullet;
class Sprite;
class Item;

class Stage1 : public Scene
{
public:
	Stage1(SceneValues* values);
	~Stage1();

	virtual void Update() override;
	virtual void Render() override;
private:
	Sprite* backGround;	
	vector<Item*> itemlist;
private:

};