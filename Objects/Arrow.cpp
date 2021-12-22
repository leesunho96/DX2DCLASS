#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(wstring spriteFile, wstring shaderFile)
{
	sprite = new Sprite(spriteFile, shaderFile, 428, 9, 435, 24);
	sprite->SetAbsoluteScale((float)10, (float)30);
	sprite->Position(0, 0);
	sprite->Rotation(0, 0, 0);
}

Arrow::~Arrow()
{
}

void Arrow::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	sprite->Position(pos);
}

void Arrow::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	sprite->Update(V, P);
}

void Arrow::Render()
{
	if (isActivate)
	{
		sprite->Render();
		ImGui::LabelText("Position :", "%.0f, %.0f", position.x, position.y);
	}
}
