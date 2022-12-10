#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

//簡單座標加減
template<typename T,typename U>
class pair {
public:
	T first;
	U second;
	pair<T, U>(){
		this->first = 0;
		this->second = 0;
	}
	pair<T, U>(T first, U second) {
		this->first = first;
		this->second = second;
	}
	pair<int,int> operator=(std::pair<int,int> p) {
		this->first = p.first;
		this->second = p.second;
		return *this;
	}
	void operator+=(pair<T, U> p) {
		this->first += p.first;
		this->second += p.second;
	}
	void operator+=(std::pair<int, int> p) {
		this->first += p.first;
		this->second += p.second;
	}
	bool operator==(std::pair<int, int> p) {
		if (this->first != p.first) return false;
		else if(this->second != p.second) return false;
		else return true;
	}
	bool operator==(pair<int, int> p) {
		if (this->first != p.first) return false;
		else if(this->second != p.second) return false;
		else return true;
	}
	bool operator!=(std::pair<int, int> p) {
		if (this->first != p.first) return true;
		else if(this->second != p.second) return true;
		else return false;
	}
	bool operator!=(pair<int, int> p) {
		if (this->first != p.first) return true;
		else if(this->second != p.second) return true;
		else return false;
	}
};


//回傳對手字母
static char getOpponentLetter(bool);
//一般檢查
static void checkBorder(pair<int, int> loc, int x, int y, bool isRed, std::string ID, std::vector<std::vector<std::string> >& board);
//將士檢查
static void checkBorderLimit(pair<int, int> loc, int x, int y, bool isRed, std::vector<std::vector<std::string> >& board);
//盤面可移動位置顯示
static void canMoveMark(pair<int, int> loc, bool isRed, std::vector<std::vector<std::string> >& board);
//拐馬腳
static bool checkHorseMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> > board);
//拐象腳
static bool checkElephantMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> > board);
//直線檢查 取得下一個有棋子的位置
static void getNextNonEmptyPosition (int x, int y, pair<int, int> &ret,  std::vector<std::vector<std::string> > board);
//座標移動
static void pairAdd(pair<int, int>& loc, int x, int y);

char getOpponentLetter(bool isRed) {
	return (isRed ? 'B' : 'R');
}

void checkBorder(pair<int, int> loc, int x, int y, bool isRed, std::string ID, std::vector<std::vector<std::string> >& board) {
	bool returnflag = true;
	if (ID[1] == 'H') returnflag = checkHorseMove(loc, x, y, board);
	if (ID[1] == 'E') returnflag = checkElephantMove(loc, x, y, board);
	if (!returnflag) return;
	loc.first += y;
	loc.second += x;
	if (loc.first > 11 || loc.first < 1) return;
	if (loc.second > 11 || loc.second < 1) return;
	else canMoveMark(loc,isRed,board);
}

void checkBorderLimit(pair<int, int> loc, int x, int y, bool isRed, std::vector<std::vector<std::string> >& board) {
	loc.first += y;
	loc.second += x;
	if (isRed) {
		if (loc.first > 3 || loc.first < 1) return;
		if (loc.second > 6 || loc.second < 4) return;
		else canMoveMark(loc, isRed, board);
	}
	else {
		if (loc.first > 10 || loc.first < 8) return;
		if (loc.second > 6 || loc.second < 4) return;
		else canMoveMark(loc, isRed, board);
	}
}

void canMoveMark(pair<int, int> loc, bool isRed, std::vector<std::vector<std::string> >& board) {
	if (isRed) {
		if (board[loc.first][loc.second].empty()) {
			board[loc.first][loc.second] = "M";
			return;
		}
		if (board[loc.first][loc.second][0] == 'B') {
			board[loc.first][loc.second] += 'M';
			return;
		}
	}
	else {
		if (board[loc.first][loc.second].empty()) {
			board[loc.first][loc.second] = "M";
			return;
		}
		if (board[loc.first][loc.second][0] == 'R') {
			board[loc.first][loc.second] += 'M';
			return;
		}
	}
}

bool checkHorseMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> >board) {
	if (x == 1 || x == -1) y /= 2;
	else x /= 2;
	loc.first += y;
	loc.second += x;
	return board[loc.first][loc.second].empty();
}

bool checkElephantMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> >board) {
	x /= 2;
	y /= 2;
	loc.first += y;
	loc.second += x;
	return board[loc.first][loc.second].empty();
}

void getNextNonEmptyPosition(int x, int y, pair<int, int>& ret, std::vector<std::vector<std::string> > board) {
	if (x == 0) {
		while (1) {
			ret.first += y;
			if (ret.first == 0 || ret.first == 12) {
				ret.first -= y;
				break;
			}
			if (!board[ret.first][ret.second].empty()) break;
		}
		return;
	}
	else {
		while (1) {
			ret.second += x;
			if (ret.second == 0 || ret.second == 10) {
				ret.second -= x;
				break;
			}
			if (!board[ret.first][ret.second].empty()) break;
		}
		return;
	}
}

void pairAdd(pair<int, int>& loc, int x, int y) {
	loc.first += y;
	loc.second += x;
	return;
}