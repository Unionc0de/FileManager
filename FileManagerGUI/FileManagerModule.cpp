#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <msclr/marshal_cppstd.h>

using namespace std;

list<string> searchFile(string path) {
	list<string> result;
	setlocale(LC_ALL, "rus");

	path += "\\*";

	WIN32_FIND_DATAA findFileData;

	HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		cerr << "Path error" << endl;
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
