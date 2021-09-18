#include "StartForm.h"
#include "GameForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Krestikinoliki::StartForm form;
	Application::Run(% form);
}

Krestikinoliki::StartForm::StartForm(void)
{
	InitializeComponent();
}

System::Void Krestikinoliki::StartForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void Krestikinoliki::StartForm::buttonStartGame_Click(System::Object^ sender, System::EventArgs^ e)
{
	int indexGameMode = listBoxGameMode->SelectedIndex;
	if (indexGameMode == -1) {
		MessageBox::Show("Выберите режим игры!", "Внимание!");
		return;
	}

	int size = Convert::ToInt32(numericUpDownSizeMap->Value);

	numericUpDownLength->Maximum = size;
	int length = Convert::ToInt32(numericUpDownLength->Value);

	
	GameForm^ form = gcnew GameForm();
	form->rows = size;
	form->columns = size;
	form->length = length;
	form->selectedGameMode = indexGameMode;
	form->Show();
	this->Hide();
}
