#include "Chess.h"

General::General(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) this->loc = std::make_pair(1, 5);
	else  this->loc = std::make_pair(10, 5);
}

void General::move(Board& Board) {
	checkBorderLimit(loc, 1, 0, isRed, 1, Board.board);
	checkBorderLimit(loc, -1, 0, isRed, 1, Board.board);
	checkBorderLimit(loc, 0, -1, isRed, 1, Board.board);
	checkBorderLimit(loc, 0, 1, isRed, 1, Board.board);
}


Warrior::Warrior(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(1, 4);
		else this->loc = std::make_pair(1, 6);
	}
	else {
		if (ID[2] == '2')this->loc = std::make_pair(10, 4);
		else this->loc = std::make_pair(10, 6);
	}
}

void Warrior::move(Board& Board) {
	checkBorderLimit(loc, 1, 1, isRed, 0, Board.board);
	checkBorderLimit(loc, -1, 1, isRed, 0, Board.board);
	checkBorderLimit(loc, 1, -1, isRed, 0, Board.board);
	checkBorderLimit(loc, -1, -1, isRed, 0, Board.board);
}



Elephant::Elephant(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(1, 3);
		else this->loc = std::make_pair(1, 7);
	}
	else {
		if (ID[2] == '2')this->loc = std::make_pair(10, 3);
		else this->loc = std::make_pair(10, 7);
	}
}

void Elephant::move(Board& Board) {
	checkBorder(loc, 2, 2, isRed, ID, Board.board);
	checkBorder(loc, -2, 2, isRed, ID, Board.board);
	checkBorder(loc, 2, -2, isRed, ID, Board.board);
	checkBorder(loc, -2, -2, isRed, ID, Board.board);
}



Horse::Horse(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(1, 2);
		else this->loc = std::make_pair(1, 8);
	}
	else {
		if (ID[2] == '2')this->loc = std::make_pair(10, 2);
		else this->loc = std::make_pair(10, 8);
	}
}

void Horse::move(Board& Board) {
	checkBorder(loc, 2, 1, isRed, ID, Board.board);
	checkBorder(loc, 2, -1, isRed, ID, Board.board);
	checkBorder(loc, -2, 1, isRed, ID, Board.board);
	checkBorder(loc, -2, -1, isRed, ID, Board.board);
	checkBorder(loc, 1, 2, isRed, ID, Board.board);
	checkBorder(loc, -1, 2, isRed, ID, Board.board);
	checkBorder(loc, 1, -2, isRed, ID, Board.board);
	checkBorder(loc, -1, -2, isRed, ID, Board.board);
}


Tank::Tank(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(1, 1);
		else this->loc = std::make_pair(1, 9);
	}
	else {
		if (ID[2] == '2')this->loc = std::make_pair(10, 1);
		else this->loc = std::make_pair(10, 9);
	}
}

void Tank::move(Board& board) {
	pair<int, int> up = loc, down = loc, left = loc, right = loc;
	getNextNonEmptyPosition(0, -1, up, board.board);
	getNextNonEmptyPosition(0, 1, down, board.board);
	getNextNonEmptyPosition(1, 0, right, board.board);
	getNextNonEmptyPosition(-1, 0, left, board.board);
	for (; up.first != loc.first; up.first++) {
		canMoveMark(up, isRed, board.board);
	}
	for (; down.first != loc.first; down.first--) {
		canMoveMark(down, isRed, board.board);
	}
	for (; left.second != loc.second; left.second++) {
		canMoveMark(left, isRed, board.board);
	}
	for (; right.second != loc.second; right.second--) {
		canMoveMark(right, isRed, board.board);
	}
}



Cannon::Cannon(std::string ID) {
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(3, 2);
		else this->loc = std::make_pair(3, 8);
	}
	else {
		if (ID[2] == '2')this->loc = std::make_pair(8, 2);
		else this->loc = std::make_pair(8, 8);
	}
}

void Cannon::move(Board& board) {
	pair<int, int> up = loc, down = loc, left = loc, right = loc;
	getNextNonEmptyPosition(0, -1, up, board.board);
	getNextNonEmptyPosition(0, 1, down, board.board);
	getNextNonEmptyPosition(1, 0, right, board.board);
	getNextNonEmptyPosition(-1, 0, left, board.board);
	if (!board.board[up.first][up.second].empty()) {
		pair<int, int> tmp = up;
		getNextNonEmptyPosition(0, -1, tmp, board.board);
		if (!board.board[tmp.first][tmp.second].empty() && tmp != up) {
			canMoveMark(tmp, isRed, board.board);
		}
		up.first++;
	}
	for (; up.first < loc.first; up.first++) {
		canMoveMark(up, isRed, board.board);
	}
	if (!board.board[down.first][down.second].empty()) {
		pair<int, int> tmp = down;
		getNextNonEmptyPosition(0, 1, tmp, board.board);
		if (!board.board[tmp.first][tmp.second].empty() && tmp != down) {
			canMoveMark(tmp, isRed, board.board);
		}
		down.first--;
	}
	for (; down.first > loc.first; down.first--) {
		canMoveMark(down, isRed, board.board);
	}
	if (!board.board[left.first][left.second].empty()) {
		pair<int, int> tmp = left;
		getNextNonEmptyPosition(-1, 0, tmp, board.board);
		if (!board.board[tmp.first][tmp.second].empty() && tmp != left) {
			canMoveMark(tmp, isRed, board.board);
		}
		left.second++;
	}
	for (; left.second < loc.second; left.second++) {
		canMoveMark(left, isRed, board.board);
	}
	if (!board.board[right.first][right.second].empty()) {
		pair<int, int> tmp = right;
		getNextNonEmptyPosition(1, 0, tmp, board.board);
		if (!board.board[tmp.first][tmp.second].empty() && tmp != right) {
			canMoveMark(tmp, isRed, board.board);
		}
		right.second--;
	}
	for (; right.second > loc.second; right.second--) {
		canMoveMark(right, isRed, board.board);
	}
}


Soldier::Soldier(std::string ID) {
	loc = pair<int, int>(3, 7);
	this->ID = ID;
	if (ID[0] == 'R') this->isRed = true;
	else this->isRed = false;
	this->deadCounter = 0;
	if (!this->isRed) {
		if (ID[2] == '1')	this->loc = std::make_pair(4, 1);
		else if (ID[2] == '2') this->loc = std::make_pair(4, 3);
		else if (ID[2] == '3') this->loc = std::make_pair(4, 5);
		else if (ID[2] == '4') this->loc = std::make_pair(4, 7);
		else if (ID[2] == '5') this->loc = std::make_pair(4, 9);
	}
	else {
		if (ID[2] == '1')	this->loc = std::make_pair(7, 9);
		else if (ID[2] == '2') this->loc = std::make_pair(7, 7);
		else if (ID[2] == '3') this->loc = std::make_pair(7, 5);
		else if (ID[2] == '4') this->loc = std::make_pair(7, 3);
		else if (ID[2] == '5') this->loc = std::make_pair(7, 1);
	}
}

void Soldier::move(Board& board) {
	if (!isRed) {
		checkBorder(loc, 0, 1, isRed, ID, board.board);
		if (this->loc.first >= 6) {
			checkBorder(loc, -1, 0, isRed, ID, board.board);
			checkBorder(loc, 1, 0, isRed, ID, board.board);
			
		}
	}
	else {
		checkBorder(loc, 0, -1, isRed, ID, board.board);
		if (this->loc.first <= 5) {
			checkBorder(loc, -1, 0, isRed, ID, board.board);
			checkBorder(loc, 1, 0, isRed, ID, board.board);
			
		}
	}
}
