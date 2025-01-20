#include <iostream>
#include <windows.h>
#include <string>
#include <list>

using namespace std;

list<string> searchFile(string path) {
    list<string> result;  // ������ ��� �������� ��������� ������ � �����
    setlocale(LC_ALL, "rus");

    // ��������� ������ "\*" ��� ������ ���� ������/����� � ����������
    path += "\\*";

    // ��������� ��� �������� ���������� � ����� ��� �����
    WIN32_FIND_DATAA findFileData;

    // ������� FindFirstFileA ���������� ���������� ������� ����� � �����
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    // ���������, ������� �� ������� �����
    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "������ ��� �������� ����������! ��������� ����." << endl;
    }
    else {
        // ���� ��� �������� ���� ������ � �����
        do {
            string fileName = findFileData.cFileName;

            // ��������� ��������� ���������� "." � ".."
            if (fileName != "." && fileName != "..") {
                result.push_back(fileName);  // ��������� ��� �����/����� � ������
            }
        } while (FindNextFileA(hFind, &findFileData) != 0); // ��������� � ���������� �����/�����

        // ��������� ����������, ����� ���������� �������
        FindClose(hFind);
    }

    return result;  // ���������� ������ ������/�����
}
