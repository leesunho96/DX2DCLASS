#include "stdafx.h"
#include "Objects/Boxes.h"
#include "Objects/Player.h"
#include "Objects/Mushroom.h"
extern Player* player;

void Boxes::isOverLapPlayer()
{
	RECT playerRECT = player->GetWorldLocation();
	RECT boxRECT = this->GetWorldLocation();
	RECT TEMP;

	if (IntersectRect(&TEMP, &playerRECT, &boxRECT) && isAvailable)
	{
		if (playerRECT.bottom < (boxRECT.top + boxRECT.bottom * 0.5f))
		{
			overlapFromUnder();
		}
	}


}

void Boxes::overlapFromUnder()
{
	isAvailable = false;
	mushroom = new Mushroom(D3DXVECTOR2(this->Position().x, this->Position().y + this->TextureSize().y * 2));
	//temp.push_back(mushroom);
}

void Boxes::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	__super::Update(V, P);


	isOverLapPlayer();
	if (mushroom != nullptr)
	{
		mushroom->Update(V, P);
	}
	
}

void Boxes::Render()
{
	__super::Render();
	if (mushroom != nullptr)
	{	
		mushroom->Render();
	}
}
