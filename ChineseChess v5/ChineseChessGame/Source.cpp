#include "GameManager.h"

void PrintBoardChess(GameManager&);
void PrintBoard(GameManager&);
int main() {
	GameManager GM;
	std::cout << "Sucessfully Generate GM\n";
	for (auto it : GM.Chesses) {
		std::cout << it.second->ID <<" ( " << it.second->loc.second << " , "<<it.second->loc.first<<" )\n";
	}
	PrintBoardChess(GM);
	std::cout << "\n";
	pair<int, int> movement(1, 1);
	GM.Chesses["RT1"]->loc += std::make_pair(4,1);
	GM.SyncBoard();
	GM.Chesses["RT1"]->move(GM.Board);
	PrintBoard(GM);
}

void PrintBoardChess(GameManager& GM) {
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 10; j++) {
			std::string s;
			for (auto it : GM.Chesses) {
				if (it.second->loc.first == i && it.second->loc.second == j) s = it.second->ID;
			}
			if (s.empty()) s = "   ";
			std::cout << s << " ";
		}
		std::cout << "\n";
	}
}

void PrintBoard(GameManager& GM) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			std::string tmp = GM.Board.board[i][j];
			if (tmp.length() < 3) tmp.insert(tmp.begin(), 3 - tmp.length(), ' ');
			std::cout << tmp;
		}
		std::cout << "\n";
	}
}