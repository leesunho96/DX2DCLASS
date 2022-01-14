#pragma once
class Player;
class Yeti;
class Character;

class ActorsData
{
public:
	ActorsData() {};
	ActorsData(Player* player) : player(player) {};
	ActorsData(Yeti* yeti) : yeti(yeti) {};
	ActorsData(Player* player, Yeti* yeti) : player(player), yeti(yeti) {};
	ActorsData(Yeti* yeti, Player* player) : yeti(yeti), player(player) {};

	void SetData(Player* player) { this->player = player; };
	void SetData(Yeti* yeti) { this->yeti = yeti; };
	void SetEnemyData(Character* character) { this->enemy = character; };


	Player* GetPlayerData() { return player; };
	Yeti* GetYetiData() { return yeti; };
	Character* GetEnemyData() { return enemy; };

	void Clear() { player = nullptr; yeti = nullptr; };
	void Clear(Yeti* yeti) { yeti = nullptr; };
	void Clear(Player* player) { player = nullptr; };
private:

	Player* player;
	Yeti* yeti;
	Character* enemy;
};

