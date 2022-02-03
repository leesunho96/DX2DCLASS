#include "stdafx.h"
#include "UI/UI.h"
#include "Data/ActorsData.h"
#include "Characters/Player.h"
#include "Characters/Goliath.h"
#include "Characters/Yeti.h"
#include "Viewer/Camera.h"
#include "Renders/AlphaBlendSprite.h"

#define YouDiedImage 0
#define YetiIntroImage 1

extern ActorsData* actorsdata;
extern int iRenderScene;


UI::UI(Player * player, Camera* camera) : target(player), camera(camera)
{
	AlphaBlendSprite* sprite;
	// YouDied SPrite
	{
		sprite = new AlphaBlendSprite(Textures + L"TianSouls/YouDIedSPrite.png", Shaders + L"010_AlphaBlend.fx");
		//sprite = new Sprite(Textures + L"TianSouls/YouDIedSPrite.png", Shaders + L"009_Sprite.fx");
		sprite->Scale(1, 1);
		sprite->Position(0, 0);
		sprite->Rotation(0, 0, 0); 
		sprite->SetAbsoluteScale(Width, Height);
		((AlphaBlendSprite*)sprite)->SetSpeed(0.3f);
		((AlphaBlendSprite*)sprite)->SetIsChangeable(true);
		((AlphaBlendSprite*)sprite)->SetFadeIn();
		vSprites.push_back(sprite);
	}	

	// Yeti
	{
		sprite = new AlphaBlendSprite(Textures + L"TianSouls/NamesSprite.png", Shaders + L"010_AlphaBlend.fx",
			0, 630, 179, 675);
		sprite->Scale(1, 1);
		sprite->SetAbsoluteScale(200, 40);
		sprite->Position(0, 0);
		sprite->Rotation(0, 0, 0);
		((AlphaBlendSprite*)sprite)->SetSpeed(0.3f);
		((AlphaBlendSprite*)sprite)->SetAlphaValues(0.9f);
		((AlphaBlendSprite*)sprite)->SetFadeOut();
		vSprites.push_back(sprite);
	}

	// Goliath
	{
		sprite = new AlphaBlendSprite(Textures + L"TianSouls/NamesSprite.png", Shaders + L"010_AlphaBlend.fx",
			0, 140, 325, 195);
		sprite->Scale(1, 1);
		sprite->SetAbsoluteScale(200, 40);
		sprite->Position(0, 0);
		sprite->Rotation(0, 0, 0);
		((AlphaBlendSprite*)sprite)->SetSpeed(0.3f);
		((AlphaBlendSprite*)sprite)->SetAlphaValues(0.9f);
		((AlphaBlendSprite*)sprite)->SetFadeOut();
		vSprites.push_back(sprite);
	}
}

UI::~UI()
{
	for (auto a : vSprites)
	{
		SAFE_DELETE(a);
	}
}

void UI::Update(D3DXMATRIX V, D3DXMATRIX & P)
{
	if (target->GetPlayerIsDied())
	{
		((AlphaBlendSprite*)vSprites[YouDiedImage])->SetValidate();
	}
	else
	{
		((AlphaBlendSprite*)vSprites[YouDiedImage])->SetInvalidate();
	}
	//int introNum;

	// intro MEssage
	{
		if (!introtemp[iRenderScene])
		{
			((AlphaBlendSprite*)vSprites[iRenderScene])->SetValidate();
			introtemp[iRenderScene] = true;
		}
		((AlphaBlendSprite*)vSprites[iRenderScene])->Position(
			camera->GetPosition() + D3DXVECTOR2(Width * 0.5f, Height * 0.5f) - D3DXVECTOR2(0, 100));
	}

	for (auto a : vSprites)
	{
		a->Update(V, P);
	}
}

void UI::Render()
{
	if (target->GetPlayerIsDied())
	{
		vSprites[YouDiedImage]->Position(camera->GetPosition() + D3DXVECTOR2(Width * 0.5f, Height * 0.5f));
		vSprites[YouDiedImage]->Render();

		if (!(((AlphaBlendSprite*)vSprites[YouDiedImage])->GetMaxAlphaValues() 
			== ((AlphaBlendSprite*)vSprites[YouDiedImage])->GetPresentAlphaValues()))
			return;

		DirectWrite::GetDC()->BeginDraw();
		DirectWrite::Get()->SetColor(D2D1::ColorF(1, 1, 0));
		{
			wstring text;
	
			RECT rect;
			rect.left = Width * 0.40;
			rect.top = Height * 0.75;
			rect.right = Width;
			rect.bottom = Height;
			text = L"Press Enter To Restart";
	
			DirectWrite::RenderText(text, rect);
		}
		DirectWrite::GetDC()->EndDraw();
	}

	if (actorsdata->isEnemyDead())
	{
		DirectWrite::GetDC()->BeginDraw();
		DirectWrite::Get()->SetColor(D2D1::ColorF(1, 1, 0));
		{
			wstring text;

			RECT rect;
			rect.left = Width * 0.40;
			rect.top = Height * 0.75;
			rect.right = Width;
			rect.bottom = Height;

			text = actorsdata->GetEnemyData() == actorsdata->GetGoliathData()
				?
				L"Press Enter To Play Next Boss" : L"THANKS FOR PLAYING";

			DirectWrite::RenderText(text, rect);
		}
		DirectWrite::GetDC()->EndDraw();
	}
	vSprites[YetiIntroImage]->Render();
}
