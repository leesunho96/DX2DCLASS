#include "stdafx.h"
#include "Marker.h"
#include "Scene/Scene.h"

extern SceneValues* values;




Marker::Marker(wstring shaderFile, D3DXVECTOR2 start)
{
	clip = new Clip(PlayMode::Loop);

	for (UINT i = 0; i < 7; i++)
	{
		float x = (float)i * 15 + 173;
		clip->AddFrame(new Sprite(Textures + L"/Mario/Bullets.png", shaderFile, x, 155, x + 11, 167), 0.3f);
	}

	position = start;
	clip->Position(position);
	clip->Play();
}

Marker::~Marker()
{
	SAFE_DELETE(clip);
}

void Marker::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 mousepos = values->MainCamera->GetPosition();
	
	// 마우스 좌클릭이 눌린 상태이며, 해당 지점이 스프라이트와 겹치는 경우
	if (clip->GetSprite()->AABB(Mouse->GetAdjustPos(mousepos)) && Mouse->Press(0))
	{
		position = Mouse->GetAdjustPos(mousepos);
	}

	clip->Position(position);
	clip->Update(V, P);
}

void Marker::Render()
{
	clip->Render();
}