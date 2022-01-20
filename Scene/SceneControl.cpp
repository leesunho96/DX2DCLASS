#include "stdafx.h"
#include "SceneControl.h"
#include "Scene.h"
#include "Scene/LoadingScene.h"
#include "Scene/Stage1.h"
#include "Scene/Stage2.h"
#include "Data/ActorsData.h"
#include "Viewer/Camera.h"
#include "Viewer/Following.h"
#include "Characters/Player.h"

#define LOADINGSCENE 0
#define YETISCENE 1
#define GOLIATHSCENE 2


#define LOADNOTHING 0
#define LOADYETIMAP 1 << 0
#define LOADGOLIATH 1 << 1

unsigned char bIsLoadingFinish = LOADNOTHING;
extern ActorsData* actorsdata;

SceneControl::SceneControl(SceneValues* value) : Scene(value)
{
	Player* player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	actorsdata = new ActorsData(player);
	iRenderScene = LOADINGSCENE;
	this->values = value;
	scenes.push_back(new LoadingScene(value));	
	scenes.push_back(nullptr);
	scenes.push_back(nullptr);
	threads.push_back(nullptr);

	//((Stage1*)scenes[GOLIATHSCENE])->ChangeCamera();
	threads.push_back
	(
		new thread
		(
			[&]()
			{
				scenes[YETISCENE] = new Stage2(value);		
				bIsLoadingFinish |= LOADYETIMAP;
			}
		)
	);
	threads.push_back
	(
		new thread
		(
			[&]()
			{
				scenes[GOLIATHSCENE] = new Stage1(value);
				bIsLoadingFinish |= LOADGOLIATH;
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
	if (actorsdata != nullptr)
	{
		actorsdata->SetEnemy(iRenderScene);
	}
	if (bIsLoadingFinish & LOADYETIMAP && Key->Down(VK_RETURN))
	{
		GoesToMap(GOLIATHSCENE);
		((Stage2*)scenes[GOLIATHSCENE])->ChangeCamera();		
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
	}
	if (threads[GOLIATHSCENE]->joinable())
	{
		threads[GOLIATHSCENE]->join();
	}
}

void SceneControl::GoesToMap(int MapNum)
{
	iRenderScene = MapNum;
}
