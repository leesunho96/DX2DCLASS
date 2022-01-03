#pragma once
class Player;
class Yeti;

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

	Player* GetPlayerData() { return player; };
	Yeti* GetYetiData() { return yeti; };
private:

	Player* player;
	Yeti* yeti;
};

