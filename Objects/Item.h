#pragma once

class Item
{
public:
	Item(int type);
	~Item();

	virtual void Update(D3DXMATRIX&V, D3DXMATRIX& P);
	virtual void Render();

	void SetPosition(D3DXVECTOR2 position) { this->position = position; sprite->Position(position); };
	bool GetIsValid() { return isvalid; };

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);
	int type;
	float speed = 50.0f;
	bool isvalid = true;

};

class ItemMemoryPool
{
public:

	ItemMemoryPool();
	~ItemMemoryPool();

	void PushItemToPool(Item * item);
	Item* GetItemFromPool();
	void CheckItemPool();

	int GetActivateItemNum() { return activateNum; };

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
private:
	vector<Item*> ItemPool;
	vector<Item*> ActivateItemVector;
	int activateNum = 0;
};