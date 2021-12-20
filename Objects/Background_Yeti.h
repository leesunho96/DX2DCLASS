#pragma once

class Sprite;
class LineDesc;

class Background_Yeti
{
public:
	Background_Yeti();
	~Background_Yeti();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	Sprite* mapSprite;

};