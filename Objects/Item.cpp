#include "stdafx.h"
#include "Objects/Item.h"
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
	position = D3DXVECTOR2(0, 0);
	sprite->Position(position);
	sprite->Scale(1, 1);
	sprite->DrawBound(true);
}

Item::~Item()
{
	SAFE_DELETE(sprite);
}

void Item::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isvalid)
		return;

	position.y -=  speed * Timer->Elapsed();
	sprite->Position(position);

	if (player->GetSprite()->Position().y <= position.y + 50.0f)
	{
		if (Sprite::AABB(sprite, player->GetSprite()))
		{
			player->GetItem(type);
			isvalid = false;
		}
	}
	if (position.y <= -100)
	{
		isvalid = false;
	}
	
}

void Item::Render()
{
	sprite->Render();
	ImGui::SliderFloat("Item Y pos", &position.y, -500, 500);
}


//
// 언팩 확인.
// 할로우 나이트
// 커비
// 쇼벨 나이트
// 림월드
// 테라리아 
// 바인딩 오브 아이작.
// 스펠렁키
// 던그리드
// 스컬 더 히어로 슬레이어
//  ?? ??타이탄 소울 https://www.spriters-resource.com/pc_computer/titansouls/


ItemMemoryPool::ItemMemoryPool()
{
	for (size_t i = 0; i < 10; i++)
	{
		ItemPool.push_back(new Item(Math::Random(0, 2)));
	}

}

ItemMemoryPool::~ItemMemoryPool()
{
	for (auto freeItem : ItemPool)
	{
		SAFE_DELETE(freeItem);
	}
	ItemPool.clear();
}

void ItemMemoryPool::PushItemToPool(Item * item)
{
	ItemPool.push_back(item);
}

Item * ItemMemoryPool::GetItemFromPool()
{
	int temp = 0;
	Item* result = ItemPool.at(temp);
	ActivateItemVector.push_back(result);
	ItemPool.erase(ItemPool.begin() + temp);
	return result;
}

void ItemMemoryPool::CheckItemPool()
{
	for (size_t i = 0; i < ActivateItemVector.size();)
	{
		if (!ActivateItemVector.at(i)->GetIsValid())
		{
			this->PushItemToPool(ActivateItemVector.at(i));
			ActivateItemVector.erase(ActivateItemVector.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void ItemMemoryPool::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (int i = 0; i < ActivateItemVector.size(); i++)
	{
		ActivateItemVector[i]->Update(V, P);
	}
}

void ItemMemoryPool::Render()
{
	for (int i = 0; i < ActivateItemVector.size(); i++)
	{
		ActivateItemVector[i]->Render();
	}
}
