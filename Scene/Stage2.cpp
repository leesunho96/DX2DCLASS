#include "stdafx.h"
#include "Stage2.h"

#include "Objects/Player.h"
#include "Objects/Marker.h"
#include "Objects/Background_Yeti.h"
#include "Objects/Icycle.h"
#include "Objects/SnowBall.h"

#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

#include "Physics/CollisionSystem.h"
#include "Systems/LineDesc.h"
#include "Data/CollisionData.h"


extern CollisionSystem* collisionsystem;
extern bool bIsDebugging;
//Following* following;
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
	
	// ForDebugging
	{
		icycle = new Icycle(1, player);
		snowball = new SnowBall();
		snowball->SetPlayer(player);
	}
}

Stage2::~Stage2()
{
	if (bIsDebugging)
	{
		//SAFE_DELETE(icycle);
	}
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

	if (bIsDebugging)
	{
		icycle->Update(V, P);
		snowball->Update(V, P);
	}
}

void Stage2::Render()
{
	bg->Render();
	collisionsystem->Render();
	player->Render();

	if (bIsDebugging)
	{
		icycle->Render();
		snowball->Render();
	}

	if (ImGui::Button("icycleActivate"))
	{
		icycle->SetPosition(D3DXVECTOR2(0, 0));
		icycle->SetValidate();
	}
	//float direction[2];
	//ImGui::SliderFloat2("direction", direction, -1.0f, 1.0f);
	if (ImGui::Button("SnowballActivate"))
	{
		snowball->SetValid();
		snowball->ResetPosition(D3DXVECTOR2(0, 0));
	}
}

