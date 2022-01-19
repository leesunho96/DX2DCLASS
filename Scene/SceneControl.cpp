#include "stdafx.h"
#include "SceneControl.h"
#include "Scene.h"
#include "Scene/LoadingScene.h"
#include "Scene/Stage2.h"
#include "Viewer/Camera.h"
#include "Viewer/Following.h"

#define LOADINGSCENE 0
#define YETISCENE 1
bool bIsLoadingFinish = false;

SceneControl::SceneControl(SceneValues* value) : Scene(value)
{
	iRenderScene = LOADINGSCENE;
	for (size_t i = 0; i < 5; i++)
	{
		isLoading.push_back(false);
	}
	this->values = value;
	scenes.push_back(new LoadingScene(value));	
	threads.push_back(nullptr);
	threads.push_back
	(
		new thread
		(
			[&]()
			{
				scenes.push_back(new Stage2(value));		
				isLoading[YETISCENE] = true;
			}
		)
	);
}

SceneControl::~SceneControl()
{
	for (auto a : scenes)
	{
		SAFE_DELETE(a);
	}
}

void SceneControl::Update()
{	
	if (isLoading[YETISCENE] && Key->Down(VK_RETURN))
	{
		GoesToMap(YETISCENE);
		((Stage2*)scenes[YETISCENE])->ChangeCamera();
		isLoading[YETISCENE] = false;
	}
	scenes[iRenderScene]->Update();
}

void SceneControl::Render()
{
	scenes[iRenderScene]->Render();
}

void SceneControl::CheckIsLoadedMap()
{
	if (threads[YETISCENE]->joinable())
	{
		threads[YETISCENE]->join();		
		bIsLoadingFinish = true;
	}
}

void SceneControl::GoesToMap(int MapNum)
{
	iRenderScene = MapNum;
}
