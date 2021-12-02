#include "stdafx.h"
#include "Objects/Bullet.h"
#include "Objects/Player.h"
#include "Objects/Bricks.h"


extern vector<IBRICKSINTERFACE*>* pbricksvector;

Bullet::Bullet()
{
	wstring ShaderName = Shaders + L"009_Sprite.fx";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	sprite = new Sprite(
		Textures + L"/Alkanoid/Bullets.png",
		shaderFile,
		216, 702,
		228, 773);

	
	sprite->DrawBound(true);
	sprite->RotationDegree(0, 0, 180);
	sprite->Scale(0.5f, 0.5f);
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
	sprite->Position(position);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (!isValid)
		return;
	position = sprite->Position();
	position.y += 1;
	sprite->Position(position);

	if (position.y >= 1000)
	{
		isValid = false;
		return;
	}
	for (auto bricks : *pbricksvector)
	{
		if (bricks->GetIsValid())
		{
			if (bricks->GetSprite()->AABB(D3DXVECTOR2(position.x, position.y + sprite->TextureSize().y * 0.5f)))
			{
				bricks->ApplyDamege();
				isValid = false;
				return;
			}
		}
	}
	sprite->Update(V, P);
}

void Bullet::Render()
{
	if (!isValid)
		return;
	sprite->Render();
}



BulletMemoryPool::BulletMemoryPool()
{
	for (size_t i = 0; i < 100; i++)
	{
		ItemPool.push_back(new Bullet());
	}

}

BulletMemoryPool::~BulletMemoryPool()
{
	for (auto freeItem : ItemPool)
	{
		SAFE_DELETE(freeItem);
	}
	ItemPool.clear();
}

void BulletMemoryPool::PushItemToPool(Bullet * item)
{
	ItemPool.push_back(item);
}

Bullet * BulletMemoryPool::GetItemFromPool()
{
	int temp = 0;
	Bullet* result = ItemPool.at(temp);
	ActivateItemVector.push_back(result);
	ItemPool.erase(ItemPool.begin() + temp);
	return result;
}

void BulletMemoryPool::CheckItemPool()
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
	activateNum = ActivateItemVector.size();
	deactivateNum = ItemPool.size();
}

void BulletMemoryPool::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (int i = 0; i < ActivateItemVector.size(); i++)
	{
		ActivateItemVector[i]->Update(V, P);
	}
}

void BulletMemoryPool::Render()
{
	for (int i = 0; i < ActivateItemVector.size(); i++)
	{
		ActivateItemVector[i]->Render();
	}
	ImGui::BulletText("Activate Bullet Num : %d", activateNum);
	ImGui::BulletText("Deactivate Bullet Num : %d", deactivateNum);
}
