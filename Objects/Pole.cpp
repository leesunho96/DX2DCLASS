#include "stdafx.h"
#include "Objects/Pole.h"
#include "Objects/Player.h"


extern Player* player;

void Pole::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	__super::Update(V, P);

	RECT temp;
	if (!isTouching)
	{
		if (player->GetWorldLocation().right >= this->Position().x - 500.0f)
		{
			if (IntersectRect(&temp, &(this->GetWorldLocation()), &(player->GetWorldLocation())))
			{
				player->StageClear();
				isTouching = true;
			}
		}
	}
}

void Pole::Render()
{

}
