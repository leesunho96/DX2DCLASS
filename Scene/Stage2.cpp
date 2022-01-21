#include "stdafx.h"
#include "Stage2.h"

#include "Characters/Player.h"
#include "Characters/Yeti.h"
#include "Objects/Marker.h"
#include "Maps/Background_Yeti.h"


#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

#include "Physics/CollisionSystem.h"

#include "Data/LineDesc.h"
#include "Data/CollisionData.h"

#include "UI/UI.h"

extern CollisionSystem* collisionsystem;
extern ActorsData* actorsdata;
//Following* following;

Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	float scale = 1.5f;
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	bg = new Background_Yeti(values, scale);
	collisionsystem = new CollisionSystem(values, player);
	//player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	player = actorsdata->GetPlayerData();
	//actorsdata->SetData(player);
	yeti = new Yeti(D3DXVECTOR2(0, 200), D3DXVECTOR2(2, 2));
	actorsdata->SetData(yeti);
	following = new Following(player);
	RECT cameraBoundery = { -(Width * 0.5f) * scale, //left
		(Height * 0.5f) * scale,  // top
		(Width * 0.5f) * scale, // right
		-(Height * 0.5f) * scale }; // bottom
	following->SetLimit(cameraBoundery, player->GetOffset());
	ui = new UI(player, following);
}

Stage2::~Stage2()
{	
	
	SAFE_DELETE(collisionsystem);
	//SAFE_DELETE(yeti);
	//SAFE_DELETE(player);
	SAFE_DELETE(bg);
	SAFE_DELETE(ui);
}

void Stage2::Update()
{
	D3DXMATRIX V = following->GetView();
	D3DXMATRIX P;// = values->Projection;
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);


	bg->Update(V, P);
	yeti->Update(V, P);
	player->Update(V, P);
	collisionsystem->Update(V, P);
	ui->Update(V, P);
}

void Stage2::Render()
{
	bg->Render();
	collisionsystem->Render();
	player->Render();
	yeti->Render();
	ui->Render();
}

void Stage2::ChangeCamera()
{
	values->MainCamera = following;
	collisionsystem->GetCollisionData(bg->GetCollisionData());
}

