#include "stdafx.h"
#include "Background.h"

Background::Background(wstring shaderFile)
{
	wstring textureFile = L"";

	//L"../_Textures/Mario/Cloud.png"

	textureFile = L"../_Textures/PuzzleBobble/puzzlebobblebackground.png";
	background = new Sprite
	(
		textureFile, shaderFile,
		18.0f, 18.0f,
		18.0f + 340.0f,18.0f + 240.0f
	);
	background->Position(Width / 2 + 23, Height / 2 - 25);
	background->Scale(Width / 320.0f, Height / 225.0f);
	
}

Background::~Background()
{
	SAFE_DELETE(background);

}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	//background->Scale(Width / 340, Height / 240);
	//background->Position(Width / 2, Height / 2);
	background->Update(V, P);

}

void Background::Render()
{
	background->Render();
}