#pragma once
#include "Utility.h"

class Board {
public:
	std::vector<std::vector<std::string> > board;
	Board();
	void reset();
	void clearChess();
};