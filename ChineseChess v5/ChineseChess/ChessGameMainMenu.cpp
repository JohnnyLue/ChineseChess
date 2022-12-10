#include "ChessGameMainMenu.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ChineseChess::ChessGameMainMenu mainMenu;
	Application::Run(%mainMenu);
}