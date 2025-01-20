#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <msclr/marshal_cppstd.h> // Äëÿ ïðåîáðàçîâàíèÿ System::String^ â std::string

using namespace std;
namespace FileManagerGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: äîáàâüòå êîä êîíñòðóêòîðà
			//
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ðåñóðñû.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ searchButton;
	protected:
	private: System::Windows::Forms::Button^ exitButton;
	private: System::Windows::Forms::TextBox^ searchTextBox;

	private: System::Windows::Forms::Label^ searchLabel;
	private: System::Windows::Forms::ListBox^ resultListBox;

	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåðåìåííàÿ êîíñòðóêòîðà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òðåáóåìûé ìåòîä äëÿ ïîääåðæêè êîíñòðóêòîðà — íå èçìåíÿéòå 
		/// ñîäåðæèìîå ýòîãî ìåòîäà ñ ïîìîùüþ ðåäàêòîðà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->exitButton = (gcnew System::Windows::Forms::Button());
			this->searchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->searchLabel = (gcnew System::Windows::Forms::Label());
			this->resultListBox = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->searchButton->Location = System::Drawing::Point(493, 525);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(154, 44);
			this->searchButton->TabIndex = 0;
			this->searchButton->Text = L"Íàéòè ôàéëû";
			this->searchButton->UseVisualStyleBackColor = true;
			this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::searchButton_Click);
			// 
			// exitButton
			// 
			this->exitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exitButton->Location = System::Drawing::Point(953, 567);
			this->exitButton->Name = L"exitButton";
			this->exitButton->Size = System::Drawing::Size(152, 42);
			this->exitButton->TabIndex = 1;
			this->exitButton->Text = L"Çàêðûòü";
			this->exitButton->UseVisualStyleBackColor = true;
			this->exitButton->Click += gcnew System::EventHandler(this, &MainForm::exitButton_Click);
			// 
			// searchTextBox
			// 
			this->searchTextBox->Location = System::Drawing::Point(418, 465);
			this->searchTextBox->Name = L"searchTextBox";
			this->searchTextBox->Size = System::Drawing::Size(305, 20);
			this->searchTextBox->TabIndex = 2;
			// 
			// searchLabel
			// 
			this->searchLabel->AutoSize = true;
			this->searchLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->searchLabel->Location = System::Drawing::Point(414, 428);
			this->searchLabel->Name = L"searchLabel";
			this->searchLabel->Size = System::Drawing::Size(219, 24);
			this->searchLabel->TabIndex = 3;
			this->searchLabel->Text = L"Ââåäèòå ïóòü äî ïàïêè";
			// 
			// resultListBox
			// 
			this->resultListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->resultListBox->FormattingEnabled = true;
			this->resultListBox->ItemHeight = 24;
			this->resultListBox->Location = System::Drawing::Point(418, 40);
			this->resultListBox->Name = L"resultListBox";
			this->resultListBox->Size = System::Drawing::Size(305, 364);
			this->resultListBox->TabIndex = 4;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1117, 621);
			this->Controls->Add(this->resultListBox);
			this->Controls->Add(this->searchLabel);
			this->Controls->Add(this->searchTextBox);
			this->Controls->Add(this->exitButton);
			this->Controls->Add(this->searchButton);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: list<string> searchFile(string path) {
		list<string> result;  // Ñïèñîê äëÿ õðàíåíèÿ íàéäåííûõ ôàéëîâ è ïàïîê
		setlocale(LC_ALL, "rus");

		// Äîáàâëÿåì øàáëîí "\*" äëÿ ïîèñêà âñåõ ôàéëîâ/ïàïîê â äèðåêòîðèè
		path += "\\*";

		// Ñòðóêòóðà äëÿ õðàíåíèÿ èíôîðìàöèè î ôàéëå èëè ïàïêå
		WIN32_FIND_DATAA findFileData;

		// Ôóíêöèÿ FindFirstFileA âîçâðàùàåò äåñêðèïòîð ïåðâîãî ôàéëà â ïàïêå
		HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

		// Ïðîâåðÿåì, óäàëîñü ëè îòêðûòü ïàïêó
		if (hFind == INVALID_HANDLE_VALUE) {
			cerr << "Îøèáêà ïðè îòêðûòèè äèðåêòîðèè! Ïðîâåðüòå ïóòü." << endl;//Помменять на MessageBox
		}
		else {
			// Öèêë äëÿ ïåðåáîðà âñåõ ôàéëîâ è ïàïîê
			do {
				string fileName = findFileData.cFileName;

				// Èñêëþ÷àåì ñèñòåìíûå äèðåêòîðèè "." è ".."
				if (fileName != "." && fileName != "..") {
					result.push_back(fileName);  // Äîáàâëÿåì èìÿ ôàéëà/ïàïêè â ñïèñîê
				}
			} while (FindNextFileA(hFind, &findFileData) != 0); // Ïåðåõîäèì ê ñëåäóþùåìó ôàéëó/ïàïêå

			// Çàêðûâàåì äåñêðèïòîð, ÷òîáû îñâîáîäèòü ðåñóðñû
			FindClose(hFind);
		}

		return result;  // Âîçâðàùàåì ñïèñîê ôàéëîâ/ïàïîê
	}
	
	private: System::Void PopulateListBox(std::list<std::string> items) {
		// Î÷èñòêà ListBox ïåðåä äîáàâëåíèåì íîâûõ ýëåìåíòîâ
		resultListBox->Items->Clear();

		// Ïðîõîä ïî ñïèñêó è äîáàâëåíèå ýëåìåíòîâ
		for (const auto& item : items) {
			// Ïðåîáðàçîâàíèå std::string â System::String^
			System::String^ managedItem = gcnew System::String(item.c_str());

			// Äîáàâëåíèå ýëåìåíòà â ListBox
			resultListBox->Items->Add(managedItem);
		}
	}

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void exitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			std::string path = msclr::interop::marshal_as<std::string>(searchTextBox->Text);
			list<string> result = searchFile(path);
			PopulateListBox(result);
		}
		catch(exception ex) {
			MessageBox::Show("Îøèáêà!!");
		}
	}
};
}
