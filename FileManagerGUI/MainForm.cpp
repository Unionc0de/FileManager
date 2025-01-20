#include "MainForm.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <list>

using namespace std;

int main() {
	FileManagerGUI::MainForm form;
	form.ShowDialog();
	return 0;
}

