#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"
#include "Systems/CollisionSystem.h"

vector<Marker*> *markerpointer = nullptr;

Sonic::Sonic(SceneValues * values) : Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);
	player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2));
	values->MainCamera = new Following(player);
	
	//((Freedom*)(values->MainCamera))->SetPosition(0, 0);

	collisionsystem = new CollisionSystem(values, player);
}

Sonic::~Sonic()
{
	SAFE_DELETE(collisionsystem);
	SAFE_DELETE(backGround);
}

D3DXVECTOR2 mpos;

void Sonic::Update()
{
	
	D3DXMATRIX V = values->MainCamera->GetView();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	D3DXVECTOR2 mouse = Mouse->Position();
	

	mpos = Mouse->GetAdjustPos(values->MainCamera->GetPosition());

	collisionsystem->Update(V, P);
	collisionsystem->CollisionTest(player->GetSprite());

	player->Update(V, P);

}

void Sonic::Render()
{
	backGround->Render();

	collisionsystem->Render();
	player->Render();
	ImGui::LabelText("MousePosition", "%.0f , %.0f", mpos.x, mpos.y);
}
