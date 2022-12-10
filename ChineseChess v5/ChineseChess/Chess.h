#pragma once
#include "Utility.h"
#include "Board.h"

class Chess {
public:
	pair<int, int> loc;
	int deadCounter=0;
	bool isRed;
	std::string ID;
	virtual void move(Board&) = 0;
};

class General :public Chess {
public:
	General(std::string);
	virtual void move(Board&);
};

class Warrior :public Chess {
public:
	Warrior(std::string);
	virtual void move(Board&);
};

class Elephant :public Chess {
public:
	Elephant(std::string);
	virtual void move(Board&);
};

class Horse :public Chess {
public:
	Horse(std::string);
	virtual void move(Board&);
};

class Tank :public Chess {
public:
	Tank(std::string);
	virtual void move(Board&);
};

class Cannon :public Chess {
public:
	Cannon(std::string);
	virtual void move(Board&);
};

class Soldier :public Chess {
public:
	Soldier(std::string);
	virtual void move(Board&);
};