#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
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
	pair<int, int> operator+(std::pair<int, int> p) {
		pair<int, int> ret;
		ret.first = p.first + this->first;
		ret.second = p.second + this->second;
		return ret;
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
static void checkBorderLimit(pair<int, int> loc, int x, int y, bool isRed, bool isGeneral, std::vector<std::vector<std::string> >& board);
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
//System String to std::String
static std::string SysStrToStdStr(System::String^);


char getOpponentLetter(bool isRed) {
	return (isRed ? 'B' : 'R');
}

void checkBorder(pair<int, int> loc, int x, int y, bool isRed, std::string ID, std::vector<std::vector<std::string> >& board) {
	bool returnflag = true;
	if (ID[1] == 'H') returnflag = checkHorseMove(loc, x, y, board);
	if (ID[1] == 'E') returnflag = checkElephantMove(loc, x, y, board);
	if (!returnflag) return;
	pair<int, int> tmp = loc;
	loc.first += y;
	loc.second += x;
	if (loc.first > 10 || loc.first < 1) return;
	if (loc.second > 9 || loc.second < 1) return;
	if (ID[1] == 'E')
	{
		if (isRed)
		{
			if (loc.first > 10 || loc.first < 6) return;
		}
		else {
			if (loc.first > 5 || loc.first < 1) return;
		}
	}
	canMoveMark(loc,isRed,board);
}

void checkBorderLimit(pair<int, int> loc, int x, int y, bool isRed, bool isGeneral, std::vector<std::vector<std::string> >& board) {
	pair<int, int> tmp = loc;
	loc.first += y;
	loc.second += x;
	if (!isRed) {
		if (loc.first > 3 || loc.first < 1) return;
		if (loc.second > 6 || loc.second < 4) return;
		if (isGeneral && !board[loc.first][loc.second].empty() && board[loc.first][loc.second][1] == 'S') return;
	}
	else {
		if (loc.first > 10 || loc.first < 8) return;
		if (loc.second > 6 || loc.second < 4) return;
		if (isGeneral && !board[loc.first][loc.second].empty() && board[loc.first][loc.second][1] == 'S') return;
	}
	std::vector<std::vector<std::string> > boardtmp = board;
	pair<int, int> RGloc, BGloc;
	boardtmp[loc.first][loc.second] = boardtmp[tmp.first][tmp.second];
	boardtmp[tmp.first][tmp.second] = "";
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			if (boardtmp[i][j] == "RG1") {
				RGloc.first = i;
				RGloc.second = j;
			}
			else if (boardtmp[i][j] == "BG1") {
				BGloc.first = i;
				BGloc.second = j;
			}
		}
	}
	if (isRed && x == 0)
	{
		getNextNonEmptyPosition(0, -1, RGloc, boardtmp);
		if (RGloc == BGloc) 
			return;
	}
	if (!isRed && x == 0)
	{
		getNextNonEmptyPosition(0, 1, BGloc, boardtmp);
		if (RGloc == BGloc)
			return;
	}
	if (isRed && y == 0)
	{
		getNextNonEmptyPosition(0, -1, RGloc, boardtmp);
		if (RGloc == BGloc)
			return;
	}
	if (!isRed && y == 0)
	{
		getNextNonEmptyPosition(0, 1, BGloc, boardtmp);
		if (RGloc == BGloc)
			return;
	}

	canMoveMark(loc, isRed, board);
}

void canMoveMark(pair<int, int> loc, bool isRed, std::vector<std::vector<std::string> >& board) {
	if (isRed) {
		if (board[loc.first][loc.second].empty()) {
			board[loc.first][loc.second] = "M";
			return;
		}
		else if (board[loc.first][loc.second][0] == 'B') {
			board[loc.first][loc.second] += 'E';//小改部分'E'
			return;
		}
	}
	else {
		if (board[loc.first][loc.second].empty()) {
			board[loc.first][loc.second] = "M";
			return;
		}
		if (board[loc.first][loc.second][0] == 'R') {
			board[loc.first][loc.second] += 'E';//小改部分'E'
			return;
		}
	}
}

bool checkHorseMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> >board) {
	if (x == 1 || x == -1) y /= 2;
	else x /= 2;
	loc.first += y;
	loc.second += x;
	if (loc.first > 10 || loc.first < 1 || loc.second>9 || loc.second < 1)
		return false;
	return board[loc.first][loc.second].empty();
}

bool checkElephantMove(pair<int, int> loc, int x, int y, std::vector<std::vector<std::string> >board) {
	x /= 2;
	y /= 2;
	loc.first += y;
	loc.second += x;
	if (loc.first > 10 || loc.first < 1 || loc.second>9 || loc.second < 1)
		return false;
	return board[loc.first][loc.second].empty();
}

void getNextNonEmptyPosition(int x, int y, pair<int, int>& ret, std::vector<std::vector<std::string> > board) {
	for (auto &it : board) {
		for (auto &it2 : it) {
			if (it2 == "M") it2.clear();
		}
	}
	if (x == 0) {
		while (1) {
			ret.first += y;
			if (ret.first == 0 || ret.first == 11) {
				ret.first -= y;
				break;
			}
			if (!board[ret.first][ret.second].empty())
				break;
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
			if (!board[ret.first][ret.second].empty())
				break;
		}
		return;
	}
}

void pairAdd(pair<int, int>& loc, int x, int y) {
	loc.first += y;
	loc.second += x;
	return;
}

std::string SysStrToStdStr(System::String^ s) {
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string ret = chars;
	return ret;
}

