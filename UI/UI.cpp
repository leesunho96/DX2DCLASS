#include "stdafx.h"
#include "UI/UI.h"
#include "Objects/Player.h"
#include "Viewer/Camera.h"

#define YouDiedImage 0

UI::UI(Player * player, Camera* camera) : target(player), camera(camera)
{
	Sprite* sprite;
	// YouDied SPrite
	{
		sprite = new Sprite(Textures + L"TianSouls/YouDIedSPrite.png", Shaders + L"010_AlphaBlend.fx");
		//sprite = new Sprite(Textures + L"TianSouls/YouDIedSPrite.png", Shaders + L"009_Sprite.fx");
		sprite->Scale(1, 1);
		sprite->Position(0, 0);
		sprite->Rotation(0, 0, 0); 
		sprite->SetAbsoluteScale(Width, Height);
	}
	
	vSprites.push_back(sprite);
}

UI::~UI()
{
	for (auto a : vSprites)
	{
		SAFE_DELETE(a);
	}
}

void UI::Update(D3DXMATRIX V, D3DXMATRIX & P)
{
	for (auto a : vSprites)
	{
		a->Update(V, P);
	}
}

void UI::Render()
{
	if (target->GetPlayerIsDied())
	{
		vSprites[YouDiedImage]->Position(camera->GetPosition() + D3DXVECTOR2(Width * 0.5f, Height * 0.5f));
		vSprites[YouDiedImage]->Render();
	}
}
