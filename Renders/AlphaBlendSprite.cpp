#include "stdafx.h"
#include "AlphaBlendSprite.h"
#include "Systems/StopWatch.h"

#define fadeout 0
#define fadein 1
#define normalmode 2
//-----------------------------------------------------------------------------
//AlphaBlendSprite
//-----------------------------------------------------------------------------

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile) : Sprite(textureFile, shaderFile), stopwatch(StopWatch())
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);	
	FadeStyle = normalmode;
	stopwatch.RetAndSetTimer(5.0f);
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float endX, float endY) :
	Sprite(textureFile, shaderFile, endX, endY), stopwatch(StopWatch())
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
	FadeStyle = normalmode;
	stopwatch.RetAndSetTimer(5.0f);
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
	: Sprite(textureFile, shaderFile, startX, startY, endX, endY), stopwatch(StopWatch())
{	
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);	
	FadeStyle = normalmode;
	stopwatch.RetAndSetTimer(5.0f);
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
		if (FadeStyle == fadeout)
		{
			alphaValues = GetMaxAlphaValues();
		}
		else if (FadeStyle == fadein)
		{
			alphaValues = 0.0f;
		}		
		return;
	}
	switch (FadeStyle)
	{
	case fadeout:
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
	case fadein:
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
	case normalmode:
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
	//if (!stopwatch.IsOver())
	//	return;
	if (!bIsValidate)
		return;

	__super::Render();
}

void AlphaBlendSprite::SetFadeOut()
{
	FadeStyle = fadeout;
	alphaValues = 0.9f;
}

void AlphaBlendSprite::SetFadeIn()
{
	FadeStyle = fadein;
	alphaValues = 0.0f;
}

void AlphaBlendSprite::SetNormalMode()
{
	FadeStyle = normalmode;
}

