#pragma once

#include "Scene/Scene.h"

// cpp���� ��� ���������� �ش� ���Ͽ��� �������� ����. ���� ����Ǿ����� �˷��ֱ� ���� ���漱��
class Player;

class Stage1 : public Scene
{
public:
	Stage1(SceneValues* values);
	~Stage1();

	virtual void Update() override;
	virtual void Render() override;
private:
	Sprite* backGround;

	Player* player;
};