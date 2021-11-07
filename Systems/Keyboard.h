#pragma once

#include <bitset>
#define KEYMAX 256

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool Down(int key);
	bool Up(int key);
	bool Press(int key);

	bool Toggle(int key);

	void setIgnore();
	void setAccept();

private:
	bool isPossible;
	bitset<KEYMAX> up;
	bitset<KEYMAX> down;
};