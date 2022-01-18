#pragma once

#include "Scene.h"

class Sprite;

class LoadingScene : public Scene
{
public:
	LoadingScene(SceneValues* values);
	~LoadingScene();

	virtual void Update() override;
	virtual void Render() override;
private:
public:
private:
	Sprite* sprite;

};
