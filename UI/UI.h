#pragma once

class Player;
class Camera;

class UI
{
public:
	UI(Player* player, Camera* camera);
	~UI();

	void Update(D3DXMATRIX V, D3DXMATRIX& P);
	void Render();
private:
public:
private:
	Player* target;
	Camera* camera;
	vector<Sprite*> vSprites;

};