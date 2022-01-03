#include "stdafx.h"
#include "Stage2.h"

#include "Objects/Player.h"
#include "Objects/Marker.h"
#include "Objects/Background_Yeti.h"


#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

#include "Physics/CollisionSystem.h"
#include "Systems/LineDesc.h"

#include "Data/CollisionData.h"


extern CollisionSystem* collisionsystem;
extern bool bIsDebugging;
//Following* following;

ActorsData* actorsdata;

Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	bg = new Background_Yeti(values);
	((Freedom*)(values->MainCamera))->SetPosition(0, 0);
	//following = new Following();
	
	collisionsystem = new CollisionSystem(values, player);
	player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	collisionsystem->GetCollisionData(bg->GetCollisionData());
	actorsdata = new ActorsData(player);

}

Stage2::~Stage2()
{

	SAFE_DELETE(collisionsystem);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
	
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	bg->Update(V, P);
	player->Update(V, P);	
	collisionsystem->Update(V, P);


}

void Stage2::Render()
{
	bg->Render();
	collisionsystem->Render();
	player->Render();

}

