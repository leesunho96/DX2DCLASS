#include "stdafx.h"
#include "UI/UI.h"
#include "Objects/Player.h"
#include "Viewer/Camera.h"
#include "Renders/AlphaBlendSprite.h"

#define YouDiedImage 0
#define YetiIntroImage 1

UI::UI(Player * player, Camera* camera) : target(player), camera(camera)
{
	Sprite* sprite;
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
	}	
	vSprites.push_back(sprite);


	{
		sprite = new AlphaBlendSprite(Textures + L"TianSouls/NamesSprite.png", Shaders + L"010_AlphaBlend.fx",
			0, 630, 179, 675);
		sprite->Scale(1, 1);
		sprite->SetAbsoluteScale(50, 10);
		sprite->Position(0, 0);
		sprite->Rotation(0, 0, 0);
		sprite->SetAbsoluteScale(Width, Height);
		((AlphaBlendSprite*)sprite)->SetAlphaValues(0.9f);
		((AlphaBlendSprite*)sprite)->SetSpeed(-0.5f);
		((AlphaBlendSprite*)sprite)->SetIsChangeable(true);
	}
	vSprites.push_back(sprite);
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
	((AlphaBlendSprite*)vSprites[YetiIntroImage])->SetValidate();
	vSprites[YetiIntroImage]->Position(target->GetSprite()->Position());
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
	}	

	DirectWrite::GetDC()->EndDraw();
	vSprites[YetiIntroImage]->Render();
}
