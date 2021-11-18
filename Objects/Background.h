#pragma once
class Background
{
public:
	Background();
	~Background();


	void Update(D3DXMATRIX& V, D3DXMATRIX P);
	void Render();

	vector<Sprite*>& GetObjects() { return objects; };
	vector<Sprite*>& GetPipes() { return Pipes; };
private:
	void SetSpriteScaleRotationPosition(Sprite* sprite, D3DXVECTOR2 position, D3DXVECTOR2 Scale = D3DXVECTOR2(2.5, 2.5));
	Sprite* CreateObject(float startX, float startY, float endX, float endY, D3DXVECTOR2 Positon, D3DXVECTOR2 Scale = D3DXVECTOR2(2.5, 2.5));
	void PushVectors(Sprite* temp) { objects.push_back(temp); };
	void PushVectoresWIthPipe(Sprite* temp) { PushVectors(temp); Pipes.push_back(temp); };
	void PushVectoresWIthBottom(Sprite* temp) { PushVectors(temp); Bottoms.push_back(temp); };

	vector<Sprite*> objects;
	vector<Sprite*> Bottoms;
	vector<Sprite*> Pipes;
 	Sprite* bgSprite;
};

