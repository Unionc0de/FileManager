#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <msclr/marshal_cppstd.h>
//#include "FileManagerModule.h"

using namespace std;
namespace FileManagerGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
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
	private: System::Windows::Forms::PictureBox^ pictureBox2;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->exitButton = (gcnew System::Windows::Forms::Button());
			this->searchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->searchLabel = (gcnew System::Windows::Forms::Label());
			this->resultListBox = (gcnew System::Windows::Forms::ListBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->searchButton->Location = System::Drawing::Point(4, 112);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(154, 44);
			this->searchButton->TabIndex = 0;
			this->searchButton->Text = L"Search files";
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
			this->exitButton->Text = L"Exit";
			this->exitButton->UseVisualStyleBackColor = true;
			this->exitButton->Click += gcnew System::EventHandler(this, &MainForm::exitButton_Click);
			// 
			// searchTextBox
			// 
			this->searchTextBox->Location = System::Drawing::Point(4, 77);
			this->searchTextBox->Name = L"searchTextBox";
			this->searchTextBox->Size = System::Drawing::Size(305, 20);
			this->searchTextBox->TabIndex = 2;
			// 
			// searchLabel
			// 
			this->searchLabel->AutoSize = true;
			this->searchLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->searchLabel->Location = System::Drawing::Point(0, 40);
			this->searchLabel->Name = L"searchLabel";
			this->searchLabel->Size = System::Drawing::Size(96, 24);
			this->searchLabel->TabIndex = 3;
			this->searchLabel->Text = L"Enter path";
			this->searchLabel->Click += gcnew System::EventHandler(this, &MainForm::searchLabel_Click);
			// 
			// resultListBox
			// 
			this->resultListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->resultListBox->FormattingEnabled = true;
			this->resultListBox->ItemHeight = 24;
			this->resultListBox->Location = System::Drawing::Point(418, 40);
			this->resultListBox->Name = L"resultListBox";
			this->resultListBox->Size = System::Drawing::Size(687, 508);
			this->resultListBox->TabIndex = 4;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(4, 225);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(370, 323);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1117, 621);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->resultListBox);
			this->Controls->Add(this->searchLabel);
			this->Controls->Add(this->searchTextBox);
			this->Controls->Add(this->exitButton);
			this->Controls->Add(this->searchButton);
			this->Name = L"MainForm";
			this->Text = L"File Manager";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
		private: list<string> searchFile(string path) {
			list<string> result;
			setlocale(LC_ALL, "rus");

			path += "\\*";

			WIN32_FIND_DATAA findFileData;

			HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

			if (hFind == INVALID_HANDLE_VALUE) {
				MessageBox::Show("Path error!!");
			}
			else {
				do {
					string fileName = findFileData.cFileName;

					if (fileName != "." && fileName != "..") {
						result.push_back(fileName);
					}
				} while (FindNextFileA(hFind, &findFileData) != 0);

				FindClose(hFind);
			}

			return result;
		}
	
	private: System::Void PopulateListBox(std::list<std::string> items) {
		resultListBox->Items->Clear();

		for (const auto& item : items) {
			System::String^ managedItem = gcnew System::String(item.c_str());


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
			MessageBox::Show("Error!!");
		}
	}
private: System::Void searchLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
