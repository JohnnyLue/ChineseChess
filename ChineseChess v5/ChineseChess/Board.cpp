#include "Board.h"
//�榡: �}��,
Board::Board() {
	reset();
}

void Board::reset() {
	this->board = { { "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9"},
					{ "1","BT1","BH1","BE1","BW1","BG1","BW2","BE2","BH2","BT2"},
					{ "2",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "3",   "","BC1",   "",   "",   "",   "",   "","BC2",   ""},
					{ "4","BS1",   "","BS2",   "","BS3",   "","BS4",   "","BS5"},
					{ "5",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "6",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "7","RS5",   "","RS4",   "","RS3",   "","RS2",   "","RS1"},
					{ "8",   "","RC2",   "",   "",   "",   "",   "","RC1",   ""},
					{ "9",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{"10","RT2","RH2","RE2","RW2","RG1","RW1","RE1","RH1","RT1"} };
}

void Board::clearChess(){
	this->board = { { "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9"},
					{ "1",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "2",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "3",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "4",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "5",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "6",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "7",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "8",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{ "9",   "",   "",   "",   "",   "",   "",   "",   "",   ""},
					{"10",   "",   "",   "",   "",   "",   "",   "",   "",   ""} };
}