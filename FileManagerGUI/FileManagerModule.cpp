#include <iostream>
#include <windows.h>
#include <string>
#include <list>

using namespace std;

list<string> searchFile(string path) {
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
