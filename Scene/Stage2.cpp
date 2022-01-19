#include "stdafx.h"
#include "Stage2.h"

#include "Objects/Player.h"
#include "Objects/Yeti.h"
#include "Objects/Marker.h"
#include "Objects/Background_Yeti.h"


#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

#include "Physics/CollisionSystem.h"

#include "Data/LineDesc.h"
#include "Data/CollisionData.h"

#include "UI/UI.h"

extern CollisionSystem* collisionsystem;
extern bool bIsDebugging;
Following* following;

ActorsData* actorsdata;

Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	float scale = 1.5f;
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	//((Freedom*)(values->MainCamera))->SetPosition(0, 0);
	bg = new Background_Yeti(values, scale);
	collisionsystem = new CollisionSystem(values, player);
	player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	actorsdata = new ActorsData(player);
	yeti = new Yeti(D3DXVECTOR2(0, 200), D3DXVECTOR2(2, 2));
	actorsdata->SetData(yeti);
	following = new Following(player);
	//values->MainCamera = following;
	RECT cameraBoundery = { -(Width * 0.5f) * scale, //left
		(Height * 0.5f) * scale,  // top
		(Width * 0.5f) * scale, // right
		-(Height * 0.5f) * scale }; // bottom
	(following)->SetLimit(cameraBoundery, player->GetOffset());
	collisionsystem->GetCollisionData(bg->GetCollisionData());
	ui = new UI(player, following);
}

Stage2::~Stage2()
{
	actorsdata->Clear();
	SAFE_DELETE(collisionsystem);
	SAFE_DELETE(yeti);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
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
}

