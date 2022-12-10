#pragma once
#include "ChineseChessRender.h"
#include "GameManager.h"
namespace ChineseChess {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	/// <summary>
	/// ChessGameMainMenu ���K�n
	/// </summary>
	public ref class ChessGameMainMenu : public System::Windows::Forms::Form
	{
	public:
		ChessGameMainMenu(void)
		{
			InitializeComponent();
			openFileDialog1 = gcnew OpenFileDialog();
			this->openFileDialog1->FileName = "Select a text file";
			this->openFileDialog1->Filter = "Text files (*.txt)|*.txt";
			this->openFileDialog1->Title = "Open text file";
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~ChessGameMainMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ NewGame;
	private: System::Windows::Forms::Button^ LoadFile;
	private: System::Windows::Forms::Button^ Leave;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;





	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->NewGame = (gcnew System::Windows::Forms::Button());
			this->LoadFile = (gcnew System::Windows::Forms::Button());
			this->Leave = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"�з���", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(398, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(147, 60);
			this->label1->TabIndex = 0;
			this->label1->Text = L"�H��";
			this->label1->Click += gcnew System::EventHandler(this, &ChessGameMainMenu::label1_Click);
			this->NewGame->BackColor = System::Drawing::Color::DarkOrange;
			//this->NewGame->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			//this->NewGame->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			this->NewGame->Font = (gcnew System::Drawing::Font(L"�з���", 16.2, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->NewGame->Location = System::Drawing::Point(363, 165);
			this->NewGame->Name = L"NewGame";
			this->NewGame->Size = System::Drawing::Size(228, 55);
			this->NewGame->TabIndex = 0;
			this->NewGame->Text = L"�s�C��";
			this->NewGame->UseVisualStyleBackColor = false;
			this->NewGame->Click += gcnew System::EventHandler(this, &ChessGameMainMenu::button1_Click);
			this->LoadFile->BackColor = System::Drawing::Color::DarkOrange;
			this->LoadFile->Font = (gcnew System::Drawing::Font(L"�з���", 16.2, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LoadFile->Location = System::Drawing::Point(363, 245);
			this->LoadFile->Name = L"LoadFile";
			this->LoadFile->Size = System::Drawing::Size(228, 55);
			this->LoadFile->TabIndex = 0;
			this->LoadFile->Text = L"Ū���s��";
			this->LoadFile->UseVisualStyleBackColor = false;
			this->LoadFile->Click += gcnew System::EventHandler(this, &ChessGameMainMenu::button2_Click);
			this->Leave->BackColor = System::Drawing::Color::DarkOrange;
			this->Leave->Font = (gcnew System::Drawing::Font(L"�з���", 16.2, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Leave->Location = System::Drawing::Point(363, 319);
			this->Leave->Name = L"Leave";
			this->Leave->Size = System::Drawing::Size(228, 55);
			this->Leave->TabIndex = 0;
			this->Leave->Text = L"���}";
			this->Leave->UseVisualStyleBackColor = false;
			this->Leave->Click += gcnew System::EventHandler(this, &ChessGameMainMenu::button3_Click);
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(942, 493);
			this->Controls->Add(this->Leave);
			this->Controls->Add(this->LoadFile);
			this->Controls->Add(this->NewGame);
			this->Controls->Add(this->label1);
			this->Name = L"ChessGameMainMenu";
			this->Text = L"�H��";
			this->Load += gcnew System::EventHandler(this, &ChessGameMainMenu::ChessGameMainMenu_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ChessGameMainMenu_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
		   //�s�C��
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		GameManager::GameManager();
		GameManager::SetGameState("NewGame");
		GameManager::EventHandle();
		ChineseChessRender^ ChessBoard = gcnew ChineseChessRender();
		this->Hide();
		ChessBoard->ShowDialog(this);   //�}�ҷs����
		if (ChessBoard->DialogResult == System::Windows::Forms::DialogResult::Cancel) this->Show();
	}
		   //Ū�����
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		GameManager::GameManager();
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				StreamReader^ din = File::OpenText(openFileDialog1->FileName);
				//SysStrToStdStr(openFileDialog1->FileName);
				String^ str;
				int count = 0;
				while ((str = din->ReadLine()) != nullptr);
				din->Close();

				GameManager::SetGameState("LoadGame");
				GameManager::EventHandle(openFileDialog1->FileName);

				ChineseChessRender^ ChessBoard = gcnew ChineseChessRender();
				this->Hide();
				ChessBoard->ShowDialog(this);   //�}�ҷs����
				if (ChessBoard->DialogResult == System::Windows::Forms::DialogResult::Cancel) this->Show();
				
			}
			catch (SecurityException^ ex) {
				throw("Security Error");
			}
		}
	}
		   //���}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		exit(0);
	}
	};
}
