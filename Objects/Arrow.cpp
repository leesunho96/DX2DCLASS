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
	stopwatch->SetTimer(1.0f);
}

Arrow::~Arrow()
{
	SAFE_DELETE(stopwatch);
}

void Arrow::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	sprite->Position(pos);
	stopwatch->ResetTimer();
	stopwatch->SetTimer(1.0f);
}

void Arrow::SetBack()
{
	if (isGoing)
	{
		this->isGoing = false;
		direction = GetArrowDirectionToPlayer(player->GetSprite()->Position());
		Rotation = GetArrowRotationByPoint(player->GetSprite()->Position(), position);
	}
}

void Arrow::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isActivate)
		return;
	stopwatch->Update();
	
	if (isGoing)
	{
		if (!stopwatch->IsOver())
		{
			position += direction * Timer->Elapsed() * 300;
			// 플레이어 Or Enemy, 충돌 체크 알고리즘 추가.
			// 
			//D3DXVec2Normalize()
			Rotation = GetArrowRotation();
		}	
	}
	else
	{
		// 플레이어에게 돌아온 경우 : deactivate 한 후, 플레이어에게 알려야함
		// 알릴 메소드 만들어야됨.
		if (player->GetSprite()->OBB(sprite))
		{
			isActivate = false;
			player->SetPlayerGetArrow();
		}
		else
		{
			position += direction * Timer->Elapsed() * 300;
		}
	}

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
	ImGui::LabelText("Rotation :", "%.0f, %.0f, %.0f", Rotation.x, Rotation.y, Rotation.z);
	
}

D3DXVECTOR3 Arrow::GetArrowRotation()
{
	// S 입력시 / 0, -1
	if (direction.x == 0 && direction.y < 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(0));
	}
	// D 입력시 / 1, 0
	else if (direction.x > 0 && direction.y == 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(90.0f));
	}
	// W 입력시 // 0, 1
	else if (direction.x == 0 && direction.y > 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(180.0f));
	}
	// A 입력시 // -1, 0
	else if (direction.x < 0 && direction.y == 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(270.0f));
	}
	// 
	else if (direction.x > 0 && direction.y < 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(45.0f));
	}
	else if (direction.x > 0 && direction.y > 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(135.0f));
	}
	else if (direction.x < 0 && direction.y > 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(225.0f));
	}
	else if (direction.x < 0 && direction.y < 0)
	{
		Rotation = D3DXVECTOR3(0, 0, Math::ToRadian(315.0f));
	}

	return Rotation;
}

D3DXVECTOR3 Arrow::GetArrowRotationByPoint(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	return D3DXVECTOR3(0, 0, atan2(point1.y - point2.y, point1.x - point2.x) + Math::ToRadian(90.0f));
}

D3DXVECTOR2 Arrow::GetArrowDirectionToPlayer(D3DXVECTOR2 playerPos)
{
	direction = playerPos - position;

	D3DXVec2Normalize(&direction, &direction);

	return direction;
	
}
	

