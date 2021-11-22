#include "stdafx.h"
#include "Objects/Mushroom.h"
#include "Objects/Player.h"

extern Player* player;

void Mushroom::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isoverlap)
	{
		__super::Update(V, P);
		RECT temp;
		if (IntersectRect(&temp, &(this->GetWorldLocation()), &(player->GetWorldLocation())))
		{
			player->GetMushroom();
			isoverlap = true;
			this->Position(D3DXVECTOR2(mushPosition.x, mushPosition.y - 1000.0f));
		}
	}

}

void Mushroom::Render()
{	
	if (!isoverlap)
	{
		__super::Render();		
	}
}
