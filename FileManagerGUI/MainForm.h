#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <msclr/marshal_cppstd.h> // Для преобразования System::String^ в std::string

using namespace std;
namespace FileManagerGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
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
			this->searchButton->Text = L"Найти файлы";
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
			this->exitButton->Text = L"Закрыть";
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
			this->searchLabel->Text = L"Введите путь до папки";
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
		list<string> result;  // Список для хранения найденных файлов и папок
		setlocale(LC_ALL, "rus");

		// Добавляем шаблон "\*" для поиска всех файлов/папок в директории
		path += "\\*";

		// Структура для хранения информации о файле или папке
		WIN32_FIND_DATAA findFileData;

		// Функция FindFirstFileA возвращает дескриптор первого файла в папке
		HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

		// Проверяем, удалось ли открыть папку
		if (hFind == INVALID_HANDLE_VALUE) {
			cerr << "Ошибка при открытии директории! Проверьте путь." << endl;
		}
		else {
			// Цикл для перебора всех файлов и папок
			do {
				string fileName = findFileData.cFileName;

				// Исключаем системные директории "." и ".."
				if (fileName != "." && fileName != "..") {
					result.push_back(fileName);  // Добавляем имя файла/папки в список
				}
			} while (FindNextFileA(hFind, &findFileData) != 0); // Переходим к следующему файлу/папке

			// Закрываем дескриптор, чтобы освободить ресурсы
			FindClose(hFind);
		}

		return result;  // Возвращаем список файлов/папок
	}
	
	private: System::Void PopulateListBox(std::list<std::string> items) {
		// Очистка ListBox перед добавлением новых элементов
		resultListBox->Items->Clear();

		// Проход по списку и добавление элементов
		for (const auto& item : items) {
			// Преобразование std::string в System::String^
			System::String^ managedItem = gcnew System::String(item.c_str());

			// Добавление элемента в ListBox
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
			MessageBox::Show("Ошибка!!");
		}
	}
};
}
