#pragma once

class Player;
//class Enemy;
class StopWatch;
class Arrow
{
public:
	Arrow(wstring spriteFile, wstring shaderFile);
	~Arrow();
	void SetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosition() { return position; };
	Sprite* GetSprite() { return sprite; };
	D3DXVECTOR2 GetTextureSize() { return sprite->TextureSize(); };

	void SetActivate(bool input) { isActivate = input; };
	void SetStart() { this->isGoing = true; };
	void SetBack();// { this->isGoing = false; };
	void SetRotation(D3DXVECTOR3 vec) { this->Rotation = vec; };
	void SetDirection(D3DXVECTOR2 vec) { this->direction = vec; };
	void SetTimer(float time) { stopwatch->SetTimer(time); };
	void SetPlayer(Player* player) { this->player = player; };
	void SetpPlayerPosition(D3DXVECTOR2* pPos) { this->pPlayerPosition = pPos; };

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	
private:
	Sprite* sprite;
	Player* player;
	StopWatch* stopwatch;
	D3DXVECTOR2 position = D3DXVECTOR2(0, 0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR2 direction = D3DXVECTOR2(0, 0);
	D3DXVECTOR2* pPlayerPosition = nullptr;
	bool isActivate = false;
	bool isGoing = true;

private:
	D3DXVECTOR3 GetArrowRotation();
	D3DXVECTOR3 GetArrowRotationByPoint(D3DXVECTOR2 point1, D3DXVECTOR2 point2);
	D3DXVECTOR2 GetArrowDirectionToPlayer(D3DXVECTOR2 playerPos);
};