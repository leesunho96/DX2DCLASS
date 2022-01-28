#pragma once

#include "stdafx.h"

enum class SpriteType
{
	Sprite = 0, Clip, Animation
};

class CollisionDesc
{
public:

	void InitializeCollisionDesc(Sprite* sprite, bool isAttackable, int collisionLayer)	
	{
		this->spritetype = SpriteType::Sprite;
		this->sprite = sprite;
		this->isAttackable = isAttackable;
		this->collisionLayer = collisionLayer;
	}
	void InitializeCollisionDesc(Clip* clip	, bool isAttackable, int collisionLayer)
	{
		this->spritetype = SpriteType::Clip;
		this->clip = clip;
		this->isAttackable = isAttackable;
		this->collisionLayer = collisionLayer;
	}
	void InitializeCollisionDesc(Animation* animation, bool isAttackable, int collisionLayer)
	{
		this->spritetype = SpriteType::Animation;
		this->animation = animation;
		this->isAttackable = isAttackable;
		this->collisionLayer = collisionLayer;
	}

	Sprite* GetSprite()
	{
		switch (spritetype)
		{
		case SpriteType::Sprite:
			return sprite;
			break;
		case SpriteType::Clip:
			return clip->GetSprite();
			break;
		case SpriteType::Animation:
			return animation->GetSprite();
			break;
		default:
			break;
		}
	};

	void AdjustPosition(D3DXVECTOR2 position)
	{
		switch (spritetype)
		{
		case SpriteType::Sprite:
			sprite->Position(position);
			break;
		case SpriteType::Clip:
			clip->Position(position);
			break;
		case SpriteType::Animation:
			animation->SetPosition(position);
			break;
		default:
			break;
		}
	};

	D3DXVECTOR2 GetPosition()
	{
		switch (spritetype)
		{
		case SpriteType::Sprite:
			return sprite->Position();
			
		case SpriteType::Clip:
			return clip->Position();
			
		case SpriteType::Animation:
			return animation->GetPosition();
			
		default:
			break;
		}
	}

	SpriteType spritetype;
	bool isAttackable;
	int collisionLayer;
	Sprite* sprite;
	Clip* clip;
	Animation* animation;
};