#pragma once
#include "Sprite.h"

class StopWatch;

class AlphaBlendSprite : public Sprite
{
public:
	AlphaBlendSprite(wstring textureFile, wstring shaderFile);
	AlphaBlendSprite(wstring texturefile, wstring shaderFile, float endX, float endY);
	AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	virtual ~AlphaBlendSprite();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	float GetMaxAlphaValues() { return 0.9f; };
	float GetPresentAlphaValues() { return alphaValues; };
	void SetAlphaValues(float input) { alphaValues = input; };
	void SetValidate() { bIsValidate = true; };
	void SetInvalidate() { bIsValidate = false; };
	void SetIsChangeable(bool input) { bIsChangeableAlphaValues = input; };
	void SetSpeed(float input) { Speed = input; };
	void SetFadeOut();
	void SetFadeIn();
	void SetNormalMode();
private:
	bool bIsValidate = false;
	bool bIsChangeableAlphaValues = false;
	float alphaValues = 0.0f;
	float Speed = 1.0f;
	unsigned char FadeStyle = 0;

	StopWatch stopwatch;
private:

};

///////////////////////////////////////////////////////////////////////////////

//class AlphaBlendSprites
//{
//private:
//	friend class AlphaBlendSprite;
//
//private:
//	static ID3D11ShaderResourceView* Load(wstring file);
//	static void Remove(wstring file);
//
//private:
//	struct SpriteDesc
//	{
//		UINT RefCount = 0;
//		ID3D11ShaderResourceView* SRV = NULL;
//	};
//
//	static map<wstring, SpriteDesc> spriteMap;
//};
