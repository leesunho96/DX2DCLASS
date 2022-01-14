#include "stdafx.h"
#include "AlphaBlendSprite.h"

#define fadeout 0
#define fadein 1
#define normalmode 2
//-----------------------------------------------------------------------------
//AlphaBlendSprite
//-----------------------------------------------------------------------------

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile) : Sprite(textureFile, shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);	
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float endX, float endY) :
	Sprite(textureFile, shaderFile, endX, endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

AlphaBlendSprite::AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
	: Sprite(textureFile, shaderFile, startX, startY, endX, endY)
{	
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);	
}

AlphaBlendSprite::~AlphaBlendSprite()
{
}

void AlphaBlendSprite::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXMATRIX temp;

	switch (FadeStyle)
	{
	case fadeout:
	{break; }
	case fadein:
	{

		break; 
	}
	case normalmode:
	{
		break; 
	}
	}


	if (!bIsValidate)
	{
		alphaValues = !bIsChangeableAlphaValues ? alphaValues : 0.0f;
		return;
	}
	if (bIsChangeableAlphaValues)
	{		
		if (alphaValues < 0.9f)
		{
			alphaValues += Timer->Elapsed() * Speed;// *Speed;
			temp._11 = alphaValues;
		}
		else
		{
			alphaValues = 0.9f;
		}
		if (alphaValues < 0)
		{
			alphaValues = 0.0f;
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
	FadeStyle = 0;
}

void AlphaBlendSprite::SetFadeIn()
{
	FadeStyle = 1;

}

void AlphaBlendSprite::SetNormalMode()
{
	FadeStyle = 2;
}

