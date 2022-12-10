#include "GameManager.h"

GameManager::GameManager() {
	NewBoard();
}

void GameManager::NewBoard() {
	this->Chesses["RG1"] = new General("RG1");
	this->Chesses["RW1"] = new Warrior("RW1");
	this->Chesses["RW2"] = new Warrior("RW2");
	this->Chesses["RE1"] = new Elephant("RE1");
	this->Chesses["RE2"] = new Elephant("RE2");
	this->Chesses["RH1"] = new Horse("RH1");
	this->Chesses["RH2"] = new Horse("RH2");
	this->Chesses["RT1"] = new Tank("RT1");
	this->Chesses["RT2"] = new Tank("RT2");
	this->Chesses["RC1"] = new Cannon("RC1");
	this->Chesses["RC2"] = new Cannon("RC2");
	this->Chesses["RS1"] = new Soldier("RS1");
	this->Chesses["RS2"] = new Soldier("RS2");
	this->Chesses["RS3"] = new Soldier("RS3");
	this->Chesses["RS4"] = new Soldier("RS4");
	this->Chesses["RS5"] = new Soldier("RS5");
	this->Chesses["BG1"] = new General("BG1");
	this->Chesses["BW1"] = new Warrior("BW1");
	this->Chesses["BW2"] = new Warrior("BW2");
	this->Chesses["BE1"] = new Elephant("BE1");
	this->Chesses["BE2"] = new Elephant("BE2");
	this->Chesses["BH1"] = new Horse("BH1");
	this->Chesses["BH2"] = new Horse("BH2");
	this->Chesses["BT1"] = new Tank("BT1");
	this->Chesses["BT2"] = new Tank("BT2");
	this->Chesses["BC1"] = new Cannon("BC1");
	this->Chesses["BC2"] = new Cannon("BC2");
	this->Chesses["BS1"] = new Soldier("BS1");
	this->Chesses["BS2"] = new Soldier("BS2");
	this->Chesses["BS3"] = new Soldier("BS3");
	this->Chesses["BS4"] = new Soldier("BS4");
	this->Chesses["BS5"] = new Soldier("BS5");
	this->Board.reset();
}

void GameManager::ClearBoard() {
	for (auto it : Chesses) {
		delete it.second;
	}
	this->Chesses.clear();
}

void GameManager::SyncBoard() {
	Board.clearChess();
	for (auto it : Chesses) {
		Board.board[it.second->loc.first][it.second->loc.second] = it.second->ID;
	}
}