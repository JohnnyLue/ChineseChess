#pragma once
#include "GameManager.h"
namespace ChineseChess {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Security;

	/// <summary>
	/// ChineseChessRender 的摘要
	/// </summary>
	public ref class ChineseChessRender : public System::Windows::Forms::Form
	{
	public:
		ChineseChessRender(void)
		{
			InitializeComponent();
			InitializeMyComponent();
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~ChineseChessRender()
		{



			if (components)
			{
				delete components;
			}
		}
	private:

		int size_x = 9;
		int size_y = 10;
	private: System::Windows::Forms::PictureBox^ ChessBoard;
	private: array<System::Windows::Forms::Button^, 2>^ arr;
	private: array<System::Drawing::Image^>^ chesses_image;
	private: int redTimer, blackTimer;
	private: Label^ redTime; Label^ blackTime;
	private: Timer^ timer;
	private:Button^ regret; Button^ BackToMainMenu; Button^ saveGame; Button^ redSurrender; Button^ blackSurrender;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;

		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ChineseChessRender::typeid));
		void InitializeMyComponent(void) {
			arr = gcnew cli::array<Button^, 2>(9, 10);

			const int x_dis = 44;
			const int y_dis = 46;
			int y_loc = 8;
			int i = 0, j = 0;
			this->SuspendLayout();
			for (int i = 0; i <= 9; i++) {
				for (int j = 0; j < 9; j++) {
					char nameIndex1 = (i + 1) + '0', nameIndex2 = (j + 1) + '0';
					if (nameIndex1 > '9')nameIndex1 = '0';
					arr[j, i] = gcnew Button();
					arr[j, i]->BackColor = System::Drawing::Color::Transparent;
					arr[j, i]->FlatAppearance->BorderSize = 0;
					arr[j, i]->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
					arr[j, i]->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
					arr[j, i]->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
					arr[j, i]->Location = System::Drawing::Point(8 + j * x_dis, y_loc + i * y_dis);
					arr[j, i]->Name = L"button" + (wchar_t)nameIndex1 + (wchar_t)nameIndex2;
					arr[j, i]->Size = System::Drawing::Size(44, 44);
					arr[j, i]->TabIndex = 14;
					arr[j, i]->UseVisualStyleBackColor = false;
					arr[j, i]->Parent = ChessBoard;
					arr[j, i]->Click += gcnew System::EventHandler(this, &ChineseChessRender::buttonClick);
				}
			}

			this->regret = gcnew Button();
			this->regret->BackColor = System::Drawing::Color::Gray;
			this->regret->FlatAppearance->BorderSize = 2;
			this->regret->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->regret->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->regret->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->regret->Location = System::Drawing::Point(550, 150);
			this->regret->Name = L"button";
			this->regret->Text = L"Regret";
			this->regret->Size = System::Drawing::Size(88, 44);
			this->regret->TabIndex = 14;
			this->regret->UseVisualStyleBackColor = false;
			this->regret->Parent = this;
			this->regret->Click += gcnew System::EventHandler(this, &ChineseChessRender::Regret);

			this->BackToMainMenu = gcnew Button();
			this->BackToMainMenu->BackColor = System::Drawing::Color::Gray;
			this->BackToMainMenu->FlatAppearance->BorderSize = 2;
			this->BackToMainMenu->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->BackToMainMenu->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->BackToMainMenu->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BackToMainMenu->Location = System::Drawing::Point(550, 250);
			this->BackToMainMenu->Name = L"button";
			this->BackToMainMenu->Text = L"Back To Main Menu";
			this->BackToMainMenu->Size = System::Drawing::Size(88, 44);
			this->BackToMainMenu->TabIndex = 14;
			this->BackToMainMenu->UseVisualStyleBackColor = false;
			this->BackToMainMenu->Parent = this;
			this->BackToMainMenu->DialogResult = System::Windows::Forms::DialogResult::Cancel;


			this->saveGame = gcnew Button();
			this->saveGame->BackColor = System::Drawing::Color::Gray;
			this->saveGame->FlatAppearance->BorderSize = 2;
			this->saveGame->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->saveGame->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->saveGame->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveGame->Location = System::Drawing::Point(550, 350);
			this->saveGame->Name = L"button";
			this->saveGame->Text = L"SaveGame";
			this->saveGame->Size = System::Drawing::Size(88, 44);
			this->saveGame->TabIndex = 14;
			this->saveGame->UseVisualStyleBackColor = false;
			this->saveGame->Parent = this;
			this->saveGame->Click += gcnew System::EventHandler(this, &ChineseChessRender::SaveGame);

			this->redSurrender = gcnew Button();
			this->redSurrender->BackColor = System::Drawing::Color::Gray;
			this->redSurrender->FlatAppearance->BorderSize = 2;
			this->redSurrender->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->redSurrender->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->redSurrender->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->redSurrender->Location = System::Drawing::Point(550, 450);
			this->redSurrender->Name = L"button";
			this->redSurrender->Text = L"投降(紅方)";
			this->redSurrender->Size = System::Drawing::Size(88, 44);
			this->redSurrender->TabIndex = 14;
			this->redSurrender->UseVisualStyleBackColor = false;
			this->redSurrender->Parent = this;
			this->redSurrender->Click += gcnew System::EventHandler(this, &ChineseChessRender::redsurr);

			this->blackSurrender = gcnew Button();
			this->blackSurrender->BackColor = System::Drawing::Color::Gray;
			this->blackSurrender->FlatAppearance->BorderSize = 2;
			this->blackSurrender->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->blackSurrender->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->blackSurrender->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->blackSurrender->Location = System::Drawing::Point(550, 50);
			this->blackSurrender->Name = L"button";
			this->blackSurrender->Text = L"投降(黑方)";
			this->blackSurrender->Size = System::Drawing::Size(88, 44);
			this->blackSurrender->TabIndex = 14;
			this->blackSurrender->UseVisualStyleBackColor = false;
			this->blackSurrender->Parent = this;
			this->blackSurrender->Click += gcnew System::EventHandler(this, &ChineseChessRender::blacksurr);

			this->timer = gcnew System::Windows::Forms::Timer();
			this->timer->Interval = 1000;
			this->timer->Tick += gcnew System::EventHandler(this, &ChineseChessRender::timer_Tick);
			this->timer->Start();
			this->redTimer = GameManager::redStartTimer;
			this->blackTimer = GameManager::blackStartTimer;

			this->redTime = gcnew Label();
			this->redTime->AutoSize = true;
			this->redTime->BackColor = System::Drawing::Color::Turquoise;
			this->redTime->Location = System::Drawing::Point(500, 420);
			this->redTime->Name = L"redTime";
			this->redTime->Size = System::Drawing::Size(180, 20);
			this->redTime->TabIndex = 1;
			//this->redTime->Text = L"紅方時間 : 10 : 00";
			this->redTime->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->blackTime = gcnew Label();
			this->blackTime->AutoSize = true;
			this->blackTime->BackColor = System::Drawing::Color::Turquoise;
			this->blackTime->Location = System::Drawing::Point(500, 100);
			this->blackTime->Name = L"blackTime";
			this->blackTime->Size = System::Drawing::Size(180, 20);
			this->blackTime->TabIndex = 1;
			//this->blackTime->Text = L"黑方時間 : 10 : 00";
			this->blackTime->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->blackTime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			this->Controls->Add(this->redTime);
			this->Controls->Add(this->blackTime);
			this->ResumeLayout();
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ChineseChessRender::typeid));
			this->ChessBoard = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessBoard))->BeginInit();
			this->SuspendLayout();
			// 
			// ChessBoard
			// 
			this->ChessBoard->BackColor = System::Drawing::Color::White;
			this->ChessBoard->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ChessBoard->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ChessBoard.Image")));
			this->ChessBoard->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ChessBoard.InitialImage")));
			this->ChessBoard->Location = System::Drawing::Point(35, 34);
			this->ChessBoard->Name = L"ChessBoard";
			this->ChessBoard->Size = System::Drawing::Size(551, 601);
			this->ChessBoard->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->ChessBoard->TabIndex = 0;
			this->ChessBoard->TabStop = false;
			// 
			// ChineseChessRender
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Turquoise;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->Controls->Add(this->ChessBoard);
			this->ForeColor = System::Drawing::Color::Black;
			this->Name = L"ChineseChessRender";
			this->Text = L"ChineseChessRender";
			this->TransparencyKey = System::Drawing::Color::Transparent;
			this->Load += gcnew System::EventHandler(this, &ChineseChessRender::ChineseChessRender_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessBoard))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ChineseChessRender_Load(System::Object^ sender, System::EventArgs^ e) {

		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ChineseChessRender::typeid));
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j < 9; j++) {
				System::String^ name = gcnew String(GameManager::Board.board[i + 1][j + 1].substr(0, 2).c_str());
				if (name->Length != 0)
				{
					arr[j, i]->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(name)));
				}
			}
		}
		redTime->Text = L"紅方時間 : " + (redTimer / 60).ToString() + L" : " + ((redTimer % 60) >= 10 ? (redTimer % 60).ToString() : L"0" + (redTimer % 60).ToString());
		blackTime->Text = L"黑方時間 : " + (blackTimer / 60).ToString() + L"  :" + ((blackTimer % 60) >= 10 ? (blackTimer % 60).ToString() : L"0" + (blackTimer % 60).ToString());
		
	}

	private: System::Void buttonClick(System::Object^ sender, System::EventArgs^ e) {
		if (GameManager::GameState == "RedWin" || GameManager::GameState == "BlackWin") return;
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ChineseChessRender::typeid));
		String^ buttonName = safe_cast<Button^>(sender)->Name;
		std::pair<int, int> p = std::make_pair(buttonName[6] - L'0', buttonName[7] - L'0');

		if (p.first == 0)
			p.first = 10;

		//std::cout << p.first << " " << p.second << "\n";

		//GameManager::MoveBoard(p);
		GameManager::EventHandle(p);

		Viewer::Update(arr, resources);//更新畫面

		if (GameManager::GameState == "RedMove" || GameManager::GameState == "BlackMove")
		{
			if (GameManager::RedCheckmate && GameManager::BlackCheckmate)
			{
				if (GameManager::GameState == "RedMove")
				{
					System::Windows::Forms::MessageBox::Show(L"紅方將軍");
					GameManager::RedCheckmate = false;
					GameManager::BlackCheckmate = false;
				}
				else
				{
					System::Windows::Forms::MessageBox::Show(L"黑方將軍");
					GameManager::BlackCheckmate = false;
					GameManager::RedCheckmate = false;
				}
			}
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
		
	}

	private: System::Void Regret(System::Object^ sender, System::EventArgs^ e) {
		if (GameManager::GameState == "RedWin" || GameManager::GameState == "BlackWin") return;
		if (GameManager::RecordTemp.empty())return;


		GameManager::RecordTemp.pop_back();//'\n'
		std::string tmp = GameManager::RecordTemp.substr(GameManager::RecordTemp.rfind('\n') + 1);

		std::pair<int, int>p, pAfter;
		p.second = tmp[tmp.find('(') + 1] - '0' + 1;
		p.first = tmp[tmp.find(')') - 1] - '0' + 1;
		pAfter.second = tmp[tmp.rfind('(') + 1] - '0' + 1;
		pAfter.first = tmp[tmp.rfind(')') - 1] - '0' + 1;
		for (auto it : GameManager::Chesses)
		{
			if (!it.second->deadCounter && it.second->loc == pAfter)
			{
				it.second->loc = p;
			}
		}

		for (auto it : GameManager::Chesses)
		{
			if(it.second->deadCounter)
				it.second->deadCounter--;
		}


		if (tmp[8] == '1')
		{
			GameManager::SetGameState("RedMove");
		}
		else {
			GameManager::SetGameState("BlackMove");
		}

		GameManager::RecordTemp = GameManager::RecordTemp.substr(0, GameManager::RecordTemp.rfind('\n') + 1);//刪除最後一項指令

		GameManager::SyncBoard();

		Viewer::Update(arr, resources);//更新畫面
	}

	private: System::Void SaveGame(System::Object^ sender, System::EventArgs^ e)
	{
		std::ifstream fileRead(GameManager::GameFile);//消除時間紀錄orEOF
		if (fileRead)
		{
			std::stringstream text;
			text << fileRead.rdbuf();
			std::string temp = text.str();
			temp.pop_back();
			temp.erase(temp.rfind('\n') + 1);
			fileRead.close();
			std::ofstream fileWrite(GameManager::GameFile);
			fileWrite.write(temp.c_str(), temp.size());
			fileWrite.close();
		}

		if (GameManager::GameFile.empty())//操作紀錄
		{
			time_t now = time(0);
			GameManager::GameFile = (std::string)"GameRecord\\" + std::ctime(&now);
			GameManager::GameFile.pop_back();
			for (int i = 0; i < GameManager::GameFile.size(); ++i)
				if (GameManager::GameFile[i] == ':')GameManager::GameFile[i] = '_';
			GameManager::GameFile += " GameRecord.txt";
			System::IO::FileStream^ t = System::IO::File::Create(gcnew System::String(GameManager::GameFile.c_str()));
			t->Close();
			GameManager::GameFile = SysStrToStdStr(System::IO::Path::GetFullPath(gcnew System::String(GameManager::GameFile.c_str())));
		}
		System::IO::FileStream^ File = gcnew System::IO::FileStream(gcnew System::String(GameManager::GameFile.c_str()), System::IO::FileMode::Append, System::IO::FileAccess::Write);
		System::IO::StreamWriter^ GameFileW = gcnew System::IO::StreamWriter(File);
		if (!GameManager::RecordTemp.empty())
		{
			GameManager::RecordTemp.pop_back();//'\n'

			GameFileW->WriteLine(gcnew System::String(GameManager::RecordTemp.c_str()));

		}

		GameFileW->WriteLine(gcnew System::String((std::to_string(redTimer) +" "+ std::to_string(blackTimer)).c_str()));//新時間紀錄

		GameFileW->Close();
		File->Close();
		GameManager::RecordTemp.clear();
		this->saveGame->Text = L"Saved";
	}
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->saveGame->Text == L"Saved") this->saveGame->Text = L"SaveGame";
		if (GameManager::GameState == "RedMove") {
			redTimer--;
			redTime->Text = L"紅方時間 : " + (redTimer / 60).ToString() + L" : " + ((redTimer % 60) >= 10 ? (redTimer % 60).ToString() : L"0" + (redTimer % 60).ToString());
		}
		else {
			blackTimer--;
			blackTime->Text = L"黑方時間 : " + (blackTimer / 60).ToString() + L"  :" + ((blackTimer % 60) >= 10 ? (blackTimer % 60).ToString() : L"0" + (blackTimer % 60).ToString());
		}
		if (redTimer == 0) {
			GameManager::GameState = "BlackWin";
			this->timer->Stop();
		}
		else if (blackTimer == 0) {
			GameManager::GameState = "RedWin";
			this->timer->Stop();
		}
		if (GameManager::GameState == "RedWin") {
			this->timer->Stop();
			if (blackTimer == 0) {
				MessageBox::Show(L"黑方時間到 ! 紅方獲勝 !!\n點選右側存檔 或者 回到主選單 開啟新遊戲 或 離開", "結束!");
			}
			else MessageBox::Show(L"紅方獲勝 !!\n點選右側存檔 或者 回到主選單 開啟新遊戲 或 離開", "結束!");
		}
		else if (GameManager::GameState == "BlackWin") {
			this->timer->Stop();
			if (redTimer == 0) {
				MessageBox::Show(L"紅方時間到 ! 黑方獲勝 !!\n點選右側存檔 或者 回到主選單 開啟新遊戲 或 離開", "結束!");
			}
			else MessageBox::Show(L"黑方獲勝 !!\n點選右側存檔 或者 回到主選單 開啟新遊戲 或 離開", "結束!");
		}
	}

	private: System::Void redsurr(System::Object^ sender, System::EventArgs^ e)
	{
		if (GameManager::GameState != "RedMove") return;
		if (MessageBox::Show(L"你真的要投降嗎", L"投降確認", System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			GameManager::GameState = "BlackWin";
		}
	}

	private: System::Void blacksurr(System::Object^ sender, System::EventArgs^ e)
	{
		if (GameManager::GameState != "BlackMove") return;
		if (MessageBox::Show(L"你真的要投降嗎", L"投降確認", System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			GameManager::GameState = "RedWin";
		}
	};


	};
}
