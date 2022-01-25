#include "stdafx.h"
#include "AlphaBlendSprite.h"
#include "Systems/StopWatch.h"

#define FADEOUT 0
#define FADEIN 1
#define NORMALMODE 2
//-----------------------------------------------------------------------------
//AlphaBlendSprite
//-----------------------------------------------------------------------------

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, FadeType fadetype) : Sprite(textureFile, shaderFile), stopwatch(StopWatch())
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
	stopwatch.RetAndSetTimer(5.0f);
	SetFadeStyle(fadetype);
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float endX, float endY, FadeType fadetype) :
	Sprite(textureFile, shaderFile, endX, endY), stopwatch(StopWatch())
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);

	stopwatch.RetAndSetTimer(5.0f);
	SetFadeStyle(fadetype);
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY, FadeType fadetype)
	: Sprite(textureFile, shaderFile, startX, startY, endX, endY), stopwatch(StopWatch())
{	
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);	
	stopwatch.RetAndSetTimer(5.0f);
	SetFadeStyle(fadetype);
}

AlphaBlendSprite::~AlphaBlendSprite()
{
}

void AlphaBlendSprite::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXMATRIX temp;

	//stopwatch.Update();

	//if (!stopwatch.IsOver())
	//	return;

	if (!bIsValidate)
	{
		if (FadeStyle == FADEOUT)
		{
			alphaValues = GetMaxAlphaValues();
		}
		else if (FadeStyle == FADEIN)
		{
			alphaValues = 0.0f;
		}		
		return;
	}
	switch (FadeStyle)
	{
	case FADEOUT:
	{
		if (alphaValues > 0.0f)
		{
			alphaValues -= Timer->Elapsed() * Speed;
		}
		else
		{
			alphaValues = 0.9f;
			this->SetInvalidate();
		}
	
		break; 
	}
	case FADEIN:
	{
		if (alphaValues < 0.9f)
		{
			alphaValues += Timer->Elapsed() * Speed;// *Speed;
		}
		else
		{
			alphaValues = 0.9f;
		}
	
		break; 
	}
	case NORMALMODE:
	{
		break; 
	}
	}
	temp._11 = alphaValues;
	shader->AsMatrix("fAlphaBlendValues")->SetMatrix(temp);
	__super::Update(V, P);
}

void AlphaBlendSprite::Render()
{
	if (!bIsValidate)
		return;

	__super::Render();
}

void AlphaBlendSprite::SetFadeOut()
{
	FadeStyle = FADEOUT;
	alphaValues = 0.9f;
}

void AlphaBlendSprite::SetFadeIn()
{
	FadeStyle = FADEIN;
	alphaValues = 0.0f;
}

void AlphaBlendSprite::SetNormalMode()
{
	FadeStyle = NORMALMODE;
}

void AlphaBlendSprite::SetFadeStyle(FadeType fadetype)
{
	switch (fadetype)
	{
	case FadeType::normal:
		SetNormalMode();
		break;
	case FadeType::fadein:
		SetFadeIn();
		break;
	case FadeType::fadeout:
		SetFadeOut();
		break;
	default:
		break;
	}

}

