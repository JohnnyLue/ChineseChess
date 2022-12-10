#include "GameManager.h"

bool GameManager::Chose = false;
Chess* GameManager::CurrentChoose;
std::string GameManager::GameState;
std::string GameManager::GameFile;
std::string GameManager::RecordTemp;
Board GameManager::Board;
std::unordered_map<std::string, Chess*>  GameManager::Chesses;
std::vector<std::string>  GameManager::GameRecord;
std::unordered_map<char,std::string> GameManager::switchName;
int GameManager::blackStartTimer;
int GameManager::redStartTimer;
bool GameManager::RedCheckmate = false;
bool GameManager::BlackCheckmate = false;


GameManager::GameManager() {
	switchName['G']="General";
	switchName['C']="Cannon";
	switchName['T']="Chariot";
	switchName['E']="Elephant";
	switchName['S']="Soldier";
	switchName['W']="Advisor";
	switchName['H']="Horse";
	NewBoard();
}

void GameManager::NewBoard() {
	ClearBoard();
	Chesses["RG1"] = new General("RG1");
	Chesses["RW1"] = new Warrior("RW1");
	Chesses["RW2"] = new Warrior("RW2");
	Chesses["RE1"] = new Elephant("RE1");
	Chesses["RE2"] = new Elephant("RE2");
	Chesses["RH1"] = new Horse("RH1");
	Chesses["RH2"] = new Horse("RH2");
	Chesses["RT1"] = new Tank("RT1");
	Chesses["RT2"] = new Tank("RT2");
	Chesses["RC1"] = new Cannon("RC1");
	Chesses["RC2"] = new Cannon("RC2");
	Chesses["RS1"] = new Soldier("RS1");
	Chesses["RS2"] = new Soldier("RS2");
	Chesses["RS3"] = new Soldier("RS3");
	Chesses["RS4"] = new Soldier("RS4");
	Chesses["RS5"] = new Soldier("RS5");
	Chesses["BG1"] = new General("BG1");
	Chesses["BW1"] = new Warrior("BW1");
	Chesses["BW2"] = new Warrior("BW2");
	Chesses["BE1"] = new Elephant("BE1");
	Chesses["BE2"] = new Elephant("BE2");
	Chesses["BH1"] = new Horse("BH1");
	Chesses["BH2"] = new Horse("BH2");
	Chesses["BT1"] = new Tank("BT1");
	Chesses["BT2"] = new Tank("BT2");
	Chesses["BC1"] = new Cannon("BC1");
	Chesses["BC2"] = new Cannon("BC2");
	Chesses["BS1"] = new Soldier("BS1");
	Chesses["BS2"] = new Soldier("BS2");
	Chesses["BS3"] = new Soldier("BS3");
	Chesses["BS4"] = new Soldier("BS4");
	Chesses["BS5"] = new Soldier("BS5");
	Board.reset();
}

void GameManager::ClearBoard() {
	for (auto it : Chesses) {
		delete it.second;
	}
	Chesses.clear();
}

void GameManager::SyncBoard() {
	Board.clearChess();
	for (auto it : Chesses) {
		if(!it.second->deadCounter) Board.board[it.second->loc.first][it.second->loc.second] = it.second->ID;
	}
}

void GameManager::EventHandle() {
	if (GameState == "NewGame") {
		goto NewGame;
	}
	else if (GameState == "LoadGame") {
		goto Error;
	}
	else if (GameState == "RedMove") {
		goto Error;
	}
	else if (GameState == "BlackMove") {
		goto Error;
	}
	else if (GameState == "RedWin") {
		goto Error;
	}
	else if (GameState == "BlackWin") {
		goto Error;
	}
	else if (GameState == "EndGame") {
		goto Error;
	}
NewGame:
	NewBoard();
	GameState = "RedMove";
	GameManager::GameFile.clear();
	GameManager::blackStartTimer = 600;
	GameManager::redStartTimer = 600;
	return;
Error:
	throw("InvalidGameState");
}

void GameManager::EventHandle(System::String^ s) {
	if (GameState == "NewGame") {
		goto Error;
	}
	else if (GameState == "LoadGame") {
		goto LoadGame;
	}
	else if (GameState == "RedMove") {
		goto Error;
	}
	else if (GameState == "BlackMove") {
		goto Error;
	}
	else if (GameState == "RedWin") {
		goto Error;
	}
	else if (GameState == "BlackWin") {
		goto Error;
	}
	else if (GameState == "EndGame") {
		goto Error;
	}
LoadGame:
	NewBoard();
	LoadBoard(s);
	return;
Error:
	throw("InvalidGameState");
}

void GameManager::EventHandle(std::pair<int, int> p) {
	if (GameState == "NewGame") {
		goto Error;
	}
	else if (GameState == "LoadGame") {
		goto Error;
	}
	else if (GameState == "RedMove") {
		goto RedMove;
	}
	else if (GameState == "BlackMove") {
		goto BlackMove;
	}
	else if (GameState == "RedWin") {
		goto Error;
	}
	else if (GameState == "BlackWin") {
		goto Error;
	}
	else if (GameState == "EndGame") {
		goto Error;
	}
Error:
	throw("InvalidGameState");
RedMove:
	GameManager::MoveBoard(p);
	CheckGeneralDie();
	return;
BlackMove:
	GameManager::MoveBoard(p);
	CheckGeneralDie();
	return;
}

void GameManager::SetGameState(System::String^ s) {
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	GameState = chars;
}

void GameManager::MoveBoard(std::pair<int, int> p)
{
	std::string current = GameManager::Board.board[p.first][p.second];

	if (current.empty()) //點空白區->取消選取
	{
		GameManager::Board.clearChess();
		SyncBoard();
		Chose = false;
		return;
	}

	/*此處只改動board資料*/
	if (current.back() == 'M')//選擇移動棋子
	{
		if (GameManager::GameState == "RedMove")
		{
			GameManager::GameState = "BlackMove";
			RecordTemp.append("Player: 1, Action: ");
		}
		else {
			GameManager::GameState = "RedMove";
			RecordTemp.append("Player: 2, Action: ");
		}
		
		RecordTemp.append(switchName[CurrentChoose->ID[1]]);

		std::stringstream ChangePos;

		char x = CurrentChoose->loc.first - 1 + '0', y = CurrentChoose->loc.second - 1 + '0';

		ChangePos << " (" << y << ", " << x << ") -> (";

		CurrentChoose->loc = p;//換位

		x = CurrentChoose->loc.first - 1 + '0', y = CurrentChoose->loc.second - 1 + '0';

		ChangePos << y << ", " << x << ")";
		RecordTemp.append(ChangePos.str());
		RecordTemp.push_back('\n');

		GameManager::Board.clearChess();
		SyncBoard();
		
		if (GameManager::Stalemate())//欠行
		{
			if (GameState == "RedMove")
				SetGameState("BlackWin");
			else if (GameState == "BlackMove")
				SetGameState("RedWin");
		}
		
		GameManager::Checkmate();

		for (auto it : GameManager::Chesses)
		{
			if (it.second->deadCounter)
				it.second->deadCounter++;
		}

		Chose = false;
	}
	else if (current.back() == 'E')//吃子
	{
		if (GameManager::GameState == "RedMove")
		{
			GameManager::GameState = "BlackMove";
			RecordTemp.append("Player: 1, Action: ");
		}
		else {
			GameManager::GameState = "RedMove";
			RecordTemp.append("Player: 2, Action: ");
		}

		RecordTemp.append(switchName[CurrentChoose->ID[1]]);

		std::stringstream ChangePos;

		char x = CurrentChoose->loc.first - 1 + '0', y = CurrentChoose->loc.second - 1 + '0';

		ChangePos <<" ("<< y<<", "<<x<<") -> (";

		CurrentChoose->loc = p;//換位

		x = CurrentChoose->loc.first - 1 + '0', y = CurrentChoose->loc.second - 1 + '0';

		ChangePos<<y<<", "<<x<<")";
		RecordTemp.append(ChangePos.str());
		RecordTemp.push_back('\n');

		for (auto it : GameManager::Chesses)
		{
			if (it.second->deadCounter)
				it.second->deadCounter++;
		}

		GameManager::Chesses[current.substr(0, 3)]->deadCounter++;


		GameManager::Board.clearChess();
		SyncBoard();
		
		if (GameManager::Stalemate())//欠行
		{
			if (GameState == "RedMove")
				SetGameState("BlackWin");
			else if (GameState == "BlackMove")
				SetGameState("RedWin");
		}
		
		GameManager::Checkmate();

		Chose = false;
	}
	else if (current.back() == 'C')//再點一次選中的>取消選中
	{
		GameManager::Board.clearChess();
		SyncBoard();
		Chose = false;
	}
	else {//點選正常棋子
		
		GameManager::Board.clearChess();
		SyncBoard();

		if (GameManager::GameState.compare("RedMove") == 0)
		{
			if (current[0] == 'B')return;
		}
		else {
			if (current[0] == 'R')return;
		}
		CurrentChoose = GameManager::Chesses[current];
		Chose = true;

		bool sandwich = false;

		pair<int, int> loc = CurrentChoose->loc;
		getNextNonEmptyPosition(0, 1, loc, GameManager::Board.board);
		if (loc == GameManager::Chesses["RG1"]->loc)
		{
			loc = CurrentChoose->loc;
			getNextNonEmptyPosition(0, -1, loc, GameManager::Board.board);
			if (loc == GameManager::Chesses["BG1"]->loc)
			{
				sandwich = true;
			}
		}
		
		CurrentChoose->move(GameManager::Board);//標記可走位置ex:"M"

		if (sandwich)
		{
			for (int i = 1; i <= 10; i++)
			{
				for (int j = 1; j <= 9; j++)
				{
					if (!GameManager::Board.board[i][j].empty() && (GameManager::Board.board[i][j] == "M" || GameManager::Board.board[i][j].back() == 'E') && j!= CurrentChoose->loc.second)
					{
						GameManager::Board.board[i][j].pop_back();
					}
				}
			}
		}

		GameManager::Board.board[p.first][p.second] += 'C';//設置選中棋子
		
	}


}

void GameManager::LoadBoard(System::String^s) {//s=檔名

	GameManager::GameFile = SysStrToStdStr(s);
	
	System::String^ line;
	std::string tmp;
	std::string times;

	System::IO::FileInfo^ File = gcnew System::IO::FileInfo(gcnew System::String(GameFile.c_str()));
	System::IO::StreamReader^ GameFileR = File->OpenText();

	while ((line = GameFileR->ReadLine())!=nullptr) {
		if (System::Char::IsDigit(line[0]))
		{
			times = SysStrToStdStr(line);
			break;
		}
		if (line[0] != L'P')break;
		tmp=SysStrToStdStr(line);
		//tmp=Player: 8{Player}, Action: 19{ChessType} (X1, Y1) -> (X2, Y2)
		std::pair<int, int>p,pAfter;
		p.second = tmp[tmp.find('(') + 1] - '0' + 1;
		p.first = tmp[tmp.find(')') - 1] - '0' + 1;
		pAfter.second = tmp[tmp.rfind('(') + 1] - '0' + 1;
		pAfter.first = tmp[tmp.rfind(')') - 1] - '0' + 1;
		for (auto it : GameManager::Chesses)
		{
			for (auto it : GameManager::Chesses)
			{
				if (it.second->deadCounter)
					it.second->deadCounter++;
			}

			if (!it.second->deadCounter && it.second->loc == p)
			{
				it.second->loc = pAfter;
			}
			else if (it.second->loc == pAfter)
			{
				it.second->deadCounter++;
			}
		}
	}
	GameFileR->Close();


	if (times.empty())
	{
		GameManager::redStartTimer = 600;
		GameManager::blackStartTimer = 600;
	}
	else {
		GameManager::redStartTimer = std::atoi(times.c_str());
		times = times.substr(times.find(' ') + 1);
		GameManager::blackStartTimer = std::atoi(times.c_str());
	}
	

	if (!tmp.empty())
	{
		if (tmp[8] == '2')
		{
			SetGameState("RedMove");
		}
		else {
			SetGameState("BlackMove");
		}
	}
	else {
		SetGameState("RedMove");
	}
	
	GameManager::SyncBoard();

	Checkmate();//檢查有無checkmate
	
	if (GameManager::RedCheckmate)
	{
		System::Windows::Forms::MessageBox::Show(L"紅方將軍");
		GameManager::RedCheckmate = false;
	}


	if (GameManager::BlackCheckmate)
	{
		System::Windows::Forms::MessageBox::Show(L"黑方將軍");
		GameManager::BlackCheckmate = false;
	}

}

void GameManager::MoveChess(std::pair<int, int> p)
{
	MoveBoard(p);
}

void GameManager::Checkmate()//no mark when called
{
		for (auto it : Chesses)
		{
			if (!it.second->deadCounter && it.second->isRed)
			{
				it.second->move(GameManager::Board);
			}
		}

		RedCheckmate = true;
		for (int i = 1; i <= 10 ; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (!GameManager::Board.board[i][j].empty())
				{
					if (GameManager::Board.board[i][j] == "BG1")
					{
						GameManager::Board.clearChess();
						GameManager::SyncBoard();
						RedCheckmate = false;
					}
				}
			}
		}
		GameManager::Board.clearChess();
		GameManager::SyncBoard();
	
		for (auto it : Chesses)
		{
			if (!it.second->deadCounter && !it.second->isRed)
			{
				it.second->move(GameManager::Board);
			}
		}

		BlackCheckmate = true;
		for (int i = 1; i <= 10 ; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (!GameManager::Board.board[i][j].empty())
				{
					if (GameManager::Board.board[i][j] == "RG1")
					{
						GameManager::Board.clearChess();
						GameManager::SyncBoard();
						BlackCheckmate = false;
					}
				}
			}
		}
	
	GameManager::Board.clearChess();
	GameManager::SyncBoard();
}


bool staleHelper(Board& board)
{
	if (GameManager::GameState == "RedMove")
	{
		for (auto it : GameManager::Chesses)
		{
			if (!it.second->deadCounter && !it.second->isRed)
			{
				it.second->move(board);
			}
		}

		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (!board.board[i][j].empty())
				{
					if (board.board[i][j] == "RG1")
					{
						return true;
					}
				}
			}
		}
	}
	else 
	{
		for (auto it : GameManager::Chesses)
		{
			if (!it.second->deadCounter && it.second->isRed)
			{
				it.second->move(board);
			}
		}

		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (!board.board[i][j].empty())
				{
					if (board.board[i][j] == "BG1")
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool GameManager::Stalemate()
{
	
	if (GameManager::GameState == "RedMove")
	{
		for (auto it : GameManager::Chesses)
		{
			if (it.second->isRed && !it.second->deadCounter)
			{
				class Board testBoard = GameManager::Board;
				it.second->move(testBoard);
				testBoard.board[it.second->loc.first][it.second->loc.second] = "";
				for (int i = 1; i <= 10; i++)
				{
					for (int j = 1; j <= 9; j++)
					{
						if (testBoard.board[i][j].empty())continue;
						if (testBoard.board[i][j].back() == 'M' )
						{
							class Board tempBoard = testBoard;
							tempBoard.board[i][j] = it.second->ID;
							for (int i = 1; i <= 10; i++)
							{
								for (int j = 1; j <= 9; j++)
								{
									if (tempBoard.board[i][j].empty())continue;

									if (tempBoard.board[i][j].back() == 'M' || tempBoard.board[i][j].back() == 'E')
										tempBoard.board[i][j].pop_back();
								}
							}
							if (staleHelper(tempBoard))
							{
								return false;
							}
						}
						else if (testBoard.board[i][j].back() == 'E')
						{
							testBoard.board[i][j].pop_back();
							GameManager::Chesses[testBoard.board[i][j]]->deadCounter++;//暫時

							class Board tempBoard = testBoard;
							tempBoard.board[i][j] = it.second->ID;
							for (int i = 1; i <= 10; i++)
							{
								for (int j = 1; j <= 9; j++)
								{
									if (tempBoard.board[i][j].empty())continue;

									if (tempBoard.board[i][j].back() == 'M' || tempBoard.board[i][j].back() == 'E')
										tempBoard.board[i][j].pop_back();
								}
							}
							
							if (staleHelper(tempBoard))
							{
								GameManager::Chesses[testBoard.board[i][j]]->deadCounter--;
								return false;
							}
							else
							{
								GameManager::Chesses[testBoard.board[i][j]]->deadCounter--;
							}
						}
					}
				}
			}
		}
	}
	else if (GameManager::GameState == "BlackMove")
	{
		for (auto it : GameManager::Chesses)
		{
			if (!it.second->isRed && !it.second->deadCounter)
			{
				class Board testBoard = GameManager::Board;
				it.second->move(testBoard);
				testBoard.board[it.second->loc.first][it.second->loc.second] = "";
				for (int i = 1; i <= 10; i++)
				{
					for (int j = 1; j <= 9; j++)
					{
						if (testBoard.board[i][j].empty())continue;
						if (testBoard.board[i][j].back() == 'M')
						{
							class Board tempBoard = testBoard;
							tempBoard.board[i][j] = it.second->ID;
							for (int i = 1; i <= 10; i++)
							{
								for (int j = 1; j <= 9; j++)
								{
									if (tempBoard.board[i][j].empty())continue;

									if (tempBoard.board[i][j].back() == 'M' || tempBoard.board[i][j].back() == 'E')
										tempBoard.board[i][j].pop_back();
								}
							}
							if (staleHelper(tempBoard))
							{
								return false;
							}
						}
						else if (testBoard.board[i][j].back() == 'E')
						{
							testBoard.board[i][j].pop_back();
							GameManager::Chesses[testBoard.board[i][j]]->deadCounter++;//暫時

							class Board tempBoard = testBoard;
							tempBoard.board[i][j] = it.second->ID;
							for (int i = 1; i <= 10; i++)
							{
								for (int j = 1; j <= 9; j++)
								{
									if (tempBoard.board[i][j].empty())continue;

									if (tempBoard.board[i][j].back() == 'M' || tempBoard.board[i][j].back() == 'E')
										tempBoard.board[i][j].pop_back();
								}
							}

							if (staleHelper(tempBoard))
							{
								GameManager::Chesses[testBoard.board[i][j]]->deadCounter--;
								return false;
							}
							else
							{
								GameManager::Chesses[testBoard.board[i][j]]->deadCounter--;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

void GameManager::CheckGeneralDie() {
	if (Chesses["RG1"]->deadCounter) GameState = "BlackWin";
	else if(Chesses["BG1"]->deadCounter)GameState = "RedWin";
}


