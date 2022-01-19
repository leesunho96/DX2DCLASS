#pragma once
#include "Scene.h"
class Scene;
class Stage2;

class SceneControl : public Scene
{
public:
	SceneControl(SceneValues* value);
	~SceneControl();

	void Update();
	void Render();
	void CheckIsLoadedMap();

	// 1 : Yeti
	void GoesToMap(int MapNum);

private:

public:

private:
	vector<Scene*> scenes;
	vector<thread*> threads;
	vector<bool> isLoading;

	int iRenderScene = 0;
};