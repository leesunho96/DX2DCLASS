#pragma once
class Background
{
public:
	Background();
	~Background();


	void Update(D3DXMATRIX& V, D3DXMATRIX P);
	void Render();

	vector<Sprite*>& GetObjects() { return objects; };
private:
	void SetSpriteScaleRotationPosition(Sprite* sprite, D3DXVECTOR2 position);
	vector<Sprite*> objects;
	Sprite* bgSprite;
};

