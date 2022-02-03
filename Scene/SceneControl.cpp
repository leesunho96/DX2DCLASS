#include "stdafx.h"
#include <mutex>
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
mutex m1;
unsigned int ID_Yeti;
unsigned int ID_Goliath;
HANDLE handle_Yeti;	
HANDLE handle_Goliath;
int iRenderScene = 0;
int iPresentAvailableStage = 0;

//unsigned int __stdcall SceneControl::LoadYeti(void* args)
//{
//	scenes[GOLIATHSCENE] = new Stage2((SceneValues*)args);
//	m1.lock();
//	bIsLoadingFinish |= LOADYETIMAP;
//	m1.unlock();
//	return 0;
//}
//
//unsigned int __stdcall SceneControl::LoadGoliath(void* args)
//{
//	scenes[GOLIATHSCENE] = new Stage1((SceneValues*) args);
//	m1.lock();
//	bIsLoadingFinish |= LOADGOLIATH;
//	m1.unlock();
//	return 0;
//}
int getAbit(char x, int n) { return (x & (1 << n)) >> n; }

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

	threads.push_back
	(
		new thread
		(
			[&]()
			{
				scenes[YETISCENE] = new Stage2(value);		
				m1.lock();
				bIsLoadingFinish |= LOADYETIMAP;
				m1.unlock();
				return;
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
				m1.lock();
				bIsLoadingFinish |= LOADGOLIATH;
				m1.unlock();
				return;
			}
		)
	);
	
	//void (SceneControl::*loadyeti)(void* args);
	//void (SceneControl::*loadgoliath)(void* args);

	//loadyeti = this->LoadYeti;
	//loadgoliath = this->LoadGoliath;


	//handle_Yeti    = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void*))loadyeti,    (void*)&values, 0, &ID_Yeti);
	//handle_Goliath = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void*))loadgoliath, (void*)&values, 0, &ID_Goliath);
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
	ChangeStage();
	scenes[iRenderScene]->Update();
}


void SceneControl::Render()
{
	scenes[iRenderScene]->Render();
}

void SceneControl::ChangeStage()
{
	// bisloadingfinish가 0이 아닌 경우 무조건 로딩 완료일것.
	if (Key->Down(VK_RETURN) && bIsLoadingFinish != 0)
	{
		switch (iPresentAvailableStage)
		{
		case 0:
			GoesToMap(GOLIATHSCENE);
			((Stage2*)scenes[GOLIATHSCENE])->ChangeCamera();
			break;
		case 1:
			GoesToMap(YETISCENE);
			((Stage2*)scenes[YETISCENE])->ChangeCamera();
		case 2:
		default:
			break;
		}
	}
}

void SceneControl::CheckIsLoadedMap()
{
	if (threads[GOLIATHSCENE]->joinable())
	{
		threads[GOLIATHSCENE]->join();
		//SAFE_DELETE(threads[GOLIATHSCENE]);
		return;
	}
	if (threads[YETISCENE]->joinable())
	{
		threads[YETISCENE]->join();
		//SAFE_DELETE(threads[YETISCENE]);
		return;
	}


	//if (getAbit(bIsLoadingFinish, 1) && (threads[GOLIATHSCENE] != nullptr))
	//{
	//	threads[GOLIATHSCENE]->join();
	//	SAFE_DELETE(threads[GOLIATHSCENE]);
	//	return;
	//}

	//if (getAbit(bIsLoadingFinish, 0) && (threads[YETISCENE] != nullptr))
	//{
	//	threads[YETISCENE]->join();
	//	SAFE_DELETE(threads[YETISCENE]);
	//	return;
	//}
	
}

void SceneControl::GoesToMap(int MapNum)
{
	iRenderScene = MapNum;
	if (actorsdata != nullptr)
	{
		actorsdata->SetEnemy(iRenderScene);
	}
}
