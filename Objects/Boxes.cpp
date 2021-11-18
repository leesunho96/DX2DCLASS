#include "stdafx.h"
#include "Objects/Boxes.h"
#include "Objects/Player.h"

extern Player* player;

void Boxes::isOverLapPlayer()
{
	RECT playerRECT = player->GetWorldLocation();
	RECT boxRECT = this->GetWorldLocation();

	RECT TEMP;
	if (IntersectRect(&TEMP, &playerRECT, &boxRECT))
	{
		if (playerRECT.bottom < (boxRECT.top + boxRECT.bottom * 0.5f))
		{
			overlapFromUnder();
		}
	}


}

void Boxes::overlapFromUnder()
{
}
