#include "stdafx.h"
#include "Stage1.h"

#include "Characters/Player.h"
#include "Characters/Goliath.h"
#include "Objects/Marker.h"
#include "Maps/Background_Goliath.h"

#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

#include "Physics/CollisionSystem.h"

#include "Data/LineDesc.h"
#include "Data/CollisionData.h"

#include "UI/UI.h"


extern CollisionSystem* collisionsystem;
extern ActorsData* actorsdata;


Stage1::Stage1(SceneValues * values) 
	: Scene(values)
{
	float scale = 1.5f;
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	bg = new Background_Goliath(values, scale);
	collisionsystem = new CollisionSystem(values, player);
	player = (Player*)actorsdata->GetPlayerData();
	following = new Following(player);
	RECT cameraBoundery = { -(Width * 0.5f) * scale, //left
		(Height * 0.5f) * scale,  // top
		(Width * 0.5f) * scale, // right
		-(Height * 0.5f) * scale }; // bottom
	D3DXVECTOR2 offset = player->GetOffset();

	following->SetLimit(cameraBoundery, 
		offset);
	goliath = new Goliath(D3DXVECTOR2(0, 150), D3DXVECTOR2(2, 2));
	actorsdata->SetData(goliath);
	ui = new UI(player, following);
}

Stage1::~Stage1()
{	
	SAFE_DELETE(collisionsystem);
	SAFE_DELETE(bg);
	SAFE_DELETE(ui);
	SAFE_DELETE(goliath);
}

void Stage1::Update()
{
	D3DXMATRIX V = following->GetView();
	D3DXMATRIX P;// = values->Projection;
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);


	goliath->Update(V, P);
	player->Update(V, P);
	bg->Update(V, P);
	collisionsystem->Update(V, P);
	ui->Update(V, P);
	
}

void Stage1::Render()
{
	bg->Render();
	collisionsystem->Render();
	player->Render();
	goliath->Render();
	ui->Render();
}

void Stage1::ChangeCamera()
{
	values->MainCamera = following;
	collisionsystem->GetCollisionData(bg->GetCollisionData());
	player->ResetPlayer(D3DXVECTOR2(0, 0));
}
