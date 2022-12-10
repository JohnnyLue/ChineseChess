#include "Viewer.h"

Viewer::Viewer() {

}

void Viewer::Update(array<System::Windows::Forms::Button^, 2>^% buttons, System::ComponentModel::ComponentResourceManager^% chesses_image) {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			std::string name = GameManager::Board.board[i+1][j+1];

			if (name.empty())
			{
				buttons[j, i]->Image = (cli::safe_cast<System::Drawing::Image^>(chesses_image->GetObject("empty.png")));
				continue;
			}

			if (name.back() == 'M') buttons[j, i]->Image = (cli::safe_cast<System::Drawing::Image^>(chesses_image->GetObject("M")));
			else if (name.back() == 'E') buttons[j, i]->Image = (cli::safe_cast<System::Drawing::Image^>(chesses_image->GetObject(gcnew System::String(name.erase(2, 1).c_str()))));
			else buttons[j, i]->Image= (cli::safe_cast<System::Drawing::Image^>(chesses_image->GetObject(gcnew System::String(name.erase(2, 1).c_str()))));
		}
			
	}
	
}