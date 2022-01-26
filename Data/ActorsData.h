#pragma once
class Player;
class Yeti;
class Character;
class Goliath;

class ActorsData
{
public:
	ActorsData() {};
	ActorsData(Player* player) : player(player) {};
	ActorsData(Yeti* yeti) : yeti(yeti) {};
	ActorsData(Player* player, Yeti* yeti) : player(player), yeti(yeti) {};
	ActorsData(Yeti* yeti, Player* player) : yeti(yeti), player(player) {};

	void SetData(Player* player) { this->player = player; };
	void SetData(Yeti* yeti) { this->yeti = yeti;};
	void SetData(Goliath* goliath) { this->goliath = goliath;};
	void SetEnemy(int val) { enemy = val == 1 ? (Character*)yeti : (Character*)goliath; };

	void SetEnemyData(Character* character) { this->enemy = character; };


	Player* GetPlayerData() { return player; };
	Yeti* GetYetiData() { return yeti; };
	Character* GetEnemyData() { return enemy; };
	Goliath* GetGoliathData() { return goliath; };

	void Clear() { player = nullptr; yeti = nullptr; };
	void Clear(Yeti* yeti) { yeti = nullptr; };
	void Clear(Player* player) { player = nullptr; };
private:

	Player* player = nullptr;
	Yeti* yeti = nullptr;
	Goliath* goliath = nullptr;
	Character* enemy = nullptr;
};

