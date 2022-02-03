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
	void ChangeStage();
	void Render();
	void CheckIsLoadedMap();

	// 1 : Yeti
	void GoesToMap(int MapNum);

private:
	unsigned int __stdcall LoadYeti(void* args);
	unsigned int __stdcall LoadGoliath(void* args);
public:

private:
	vector<Scene*> scenes;
	vector<thread*> threads;
	//vector<bool> isLoading;

	
};