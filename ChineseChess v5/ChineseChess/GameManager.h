#pragma once
#include "Utility.h"
#include "Board.h"
#include "Chess.h"
#include "Viewer.h"

class GameManager {
public:
	GameManager();
	static Chess* CurrentChoose;
	static bool Chose;
	static void NewBoard();
	static void ClearBoard();
	static void SyncBoard();
	static void LoadBoard(System::String^ s);
	static void SetGameState(System::String^);
	static void EventHandle(std::pair<int, int>);
	static void EventHandle(System::String^);
	static void EventHandle();
	static void MoveBoard(std::pair<int, int>);
	static void MoveChess(std::pair<int, int>);
	static bool Stalemate();
	static void Checkmate();
	static void CheckGeneralDie();
	static std::string GameFile;
	static std::string GameState;
	static std::string RecordTemp;
	static Board Board;
	static std::unordered_map<std::string, Chess*> Chesses;
	static std::vector<std::string> GameRecord;
	static std::unordered_map<char, std::string> switchName;
	static int blackStartTimer;
	static int redStartTimer;
	static bool RedCheckmate;
	static bool BlackCheckmate;
};

