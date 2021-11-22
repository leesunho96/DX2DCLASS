#pragma once

class Pole : public Sprite
{
public:
	Pole() : Sprite(Textures + L"/Mario/SuperMarioStage1.png", Shaders + L"009_Sprite.fx",
		3160, 40, 3183, 208)
	{};

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

private:
	bool isTouching = false;
};