#pragma once
#include "Sprite.h"

enum class FadeType
{
	normal = 0, fadein, fadeout
};

class StopWatch;

class AlphaBlendSprite : public Sprite
{
public:
	AlphaBlendSprite(wstring textureFile, wstring shaderFile, FadeType fadetype = FadeType::normal);
	AlphaBlendSprite(wstring texturefile, wstring shaderFile, float endX, float endY, FadeType fadetype = FadeType::normal);
	AlphaBlendSprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY, FadeType fadetype = FadeType::normal);
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
	void SetFadeStyle(FadeType fadetype);
private:
	bool bIsValidate = false;
	bool bIsChangeableAlphaValues = false;
	float alphaValues = 0.0f;
	float Speed = 1.0f;
	unsigned char FadeStyle = 0;

	StopWatch stopwatch;
private:

};

