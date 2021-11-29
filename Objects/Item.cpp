#include "stdafx.h"
#include "Objects/Item.h"
#include "Renders/Sprite.h"
#include "Objects/Player.h"

extern Player* player;

Item::Item(int type) : type(type)
{

	wstring TexturesName = Textures + L"/Alkanoid/Blocks.png";
	wstring ShaderName = Shaders + L"009_Sprite.fx";

	switch (type)
	{
	case 0:
		sprite = new Sprite(TexturesName, ShaderName, 594, 308, 648, 329);
		break;
	case 1:
		sprite = new Sprite(TexturesName, ShaderName, 594, 308, 648, 329);
		break;
	case 2:
		sprite = new Sprite(TexturesName, ShaderName, 594, 308, 648, 329);
		break;
	}
}

Item::~Item()
{
}

void Item::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position.y -= speed * Timer->Elapsed();
	sprite->Position(position);

	if (player->GetSprite()->Position().y <= position.y + 50.0f)
	{
		if (Sprite::AABB(sprite, player->GetSprite()))
		{
			player->GetItem(type);
		}
	}
}

void Item::Render()
{
}
