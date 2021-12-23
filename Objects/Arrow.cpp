#include "stdafx.h"
#include "Arrow.h"
#include "Player.h"

Arrow::Arrow(wstring spriteFile, wstring shaderFile)
{
	sprite = new Sprite(spriteFile, shaderFile, 428, 9, 435, 24);
	sprite->SetAbsoluteScale((float)10, (float)30);
	sprite->Position(0, 0);
	sprite->Rotation(0, 0, 0);

	stopwatch = new StopWatch();
	stopwatch->SetTimer(3.0f);
}

Arrow::~Arrow()
{
	SAFE_DELETE(stopwatch);
}

void Arrow::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	sprite->Position(pos);
}

void Arrow::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isActivate)
		return;
	stopwatch->Update();
	
	if (!stopwatch->IsOver())
	{
		position += *D3DXVec2Normalize(&direction, &direction);
		// 플레이어 Or Enemy, 충돌 체크 알고리즘 추가.
		// 
		//D3DXVec2Normalize()
	}

	
	
	Rotation = GetArrowRotation();
	sprite->Rotation(Rotation);
	sprite->Position(position);
	sprite->Update(V, P);
}

void Arrow::Render()
{
	if (!isActivate)
		return;

	sprite->Render();
	ImGui::LabelText("Position :", "%.0f, %.0f", position.x, position.y);
	
}

D3DXVECTOR3 Arrow::GetArrowRotation()
{
	return D3DXVECTOR3(0, 0, 0);
}
	

