#pragma once
#include "Utility.h"
#include "Board.h"
#include "Chess.h"
#include "Viewer.h"

class GameManager {
public:
	GameManager();
	void NewBoard();
	void ClearBoard();
	void SyncBoard();
	std::string GameState;
	Board Board;
	std::unordered_map<std::string, Chess*> Chesses;
	Viewer Viewer;
};