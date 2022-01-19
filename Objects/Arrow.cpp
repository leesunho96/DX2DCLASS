#include "stdafx.h"
#include "Arrow.h"
#include "Player.h"
#include "Yeti.h"

extern ActorsData* actorsdata;

Arrow::Arrow(wstring spriteFile, wstring shaderFile)
{
	sprite = new Sprite(spriteFile, shaderFile, 428, 9, 435, 24);
	//sprite = new Sprite(spriteFile, Shaders + L"010_AlphaBlend.fx", 428, 9, 435, 24);
	sprite->SetAbsoluteScale((float)10, (float)30);
	sprite->Position(0, 0);
	sprite->Rotation(0, 0, 0);
	sprite->DrawBound(true);
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

D3DXVECTOR2 Arrow::GetTipPosistion()
{
	D3DXVECTOR2 result = position;
	result += D3DXVECTOR2(cosf(Rotation.z), cosf(Rotation.z)) * sprite->TextureSize().y * 0.5f;
	return result;
}

void Arrow::SetBack()
{
	if (isGoing)
	{
		this->isGoing = false;
		SetArrowGoesToPlayer();
	}
	
}

void Arrow::SetArrowGoesToPlayer()
{
	direction = GetArrowDirectionToPlayer(player->GetSprite()->Position());
	Rotation = GetArrowRotationByPoint(player->GetSprite()->Position(), position);
	stopwatch->SetTimer(2.0f);
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
			if (actorsdata->GetYetiData()->GetSprite()->OBB(sprite))
			{
				AttackToEnemy();
			}
			if (player->GetSprite()->OBB(sprite))
			{
				isActivate = false;
				player->SetPlayerGetArrow();
			}
		}
	}
	else
	{
		if (stopwatch->IsOver())
		{
			SetArrowGoesToPlayer();
		}
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
			if (actorsdata->GetYetiData()->GetSprite()->OBB(sprite))
			{
				AttackToEnemy();
			}
		}
	}
	sprite->Rotation(Rotation);
	sprite->Position(position);
	sprite->Update(V, P);
}

void Arrow::AttackToEnemy()
{
	if (actorsdata->GetYetiData()->IsAttackable())
	{
		actorsdata->GetYetiData()->ApplyDamege(sprite);
	}
	else
	{
		if (actorsdata->GetYetiData()->IsIdle())
		{
			actorsdata->GetYetiData()->ApplyDamege(sprite);
		}
		direction = GetReflectionVector(direction, GetWhichSideIsCollideWighEnemy(actorsdata->GetYetiData()->GetSprite()));
		position += direction * 30.0f;
	}
}

void Arrow::Render()
{
	if (!isActivate)
		return;

	D3DXVECTOR2 tippos = GetTipPosistion();
	ImGui::LabelText("TipPos : ", "%.0f, %.0f", tippos.x, tippos.y);
	sprite->Render();
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


D3DXVECTOR2 Arrow::GetReflectionVector(D3DXVECTOR2 velocity, int itype)
{
	D3DXVECTOR2 v2n;

	switch (itype)
	{
	case 0:
		v2n = D3DXVECTOR2(0, 1);
		break;
	case 1:
		v2n = D3DXVECTOR2(0, -1);
		break;
	case 2:
		v2n = D3DXVECTOR2(1, 0);
		break;
	case 3:
		v2n = D3DXVECTOR2(-1, 0);
		break;
	}

	return velocity + 2 * v2n *(D3DXVec2Dot(&(-velocity), &v2n));
}

int	Arrow::GetWhichSideIsCollideWighEnemy(Sprite* enemy)
{
	int result;
	RECT intersectRECT;
	RECT ArrowRECT;
	RECT enemyRECT;

	ArrowRECT.top    = GetTipPosistion().y - 10; //sprite->Position().y - sprite->TextureSize().y * 0.5f;
	ArrowRECT.bottom = GetTipPosistion().y + 10;//sprite->Position().y + sprite->TextureSize().y * 0.5f;
	ArrowRECT.left   = GetTipPosistion().x - 10; //sprite->Position().x - sprite->TextureSize().x * 0.5f;
	ArrowRECT.right  = GetTipPosistion().x + 10;//sprite->Position().x + sprite->TextureSize().x * 0.5f;

	enemyRECT.top = actorsdata->GetYetiData()->GetSprite()->Position().y -
		actorsdata->GetYetiData()->GetSprite()->TextureSize().y * 0.5f;
	enemyRECT.bottom = actorsdata->GetYetiData()->GetSprite()->Position().y +
		actorsdata->GetYetiData()->GetSprite()->TextureSize().y * 0.5f;
	enemyRECT.left = actorsdata->GetYetiData()->GetSprite()->Position().x -
		actorsdata->GetYetiData()->GetSprite()->TextureSize().x * 0.5f;
	enemyRECT.right = actorsdata->GetYetiData()->GetSprite()->Position().x +
		actorsdata->GetYetiData()->GetSprite()->TextureSize().x * 0.5f;

	IntersectRect(&intersectRECT, &ArrowRECT, &enemyRECT);

	// 교차하는 사각형의 길이가 가로보다 세로가 길다 => 좌/우
	if (abs(intersectRECT.bottom - intersectRECT.top) > abs(intersectRECT.right - intersectRECT.left))
	{
		// 가로가 세로보다 길고, enemy의 x좌표가 arrow의 x좌표보다 클 경우 : 화살이 enemy의 좌측으로 충돌
		if (enemy->Position().x > sprite->Position().x)
		{
			result = 2;
		}
		// 우측으로 충돌
		else
		{
			result = 3;
		}
	}
	// 교차하는 사각형의 길이가 가로보다 세로가 짧거나 같다 => 상/하
	else
	{
		if (enemy->Position().y > sprite->Position().y)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}
	}
	return result;
}
