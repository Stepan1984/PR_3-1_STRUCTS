#pragma once
#include "work_with_files.h"


using namespace std;

int ReadFile(string& filename, int n) // функция чтения файла
{
    int i = 0, itmp;
    ifstream fin; // создаём поток
    fin.exceptions(ifstream::badbit | ifstream::failbit); // для обработки исключительных ситуаций при открытие
    try
    {
        fin.open(filename); // открываем поток на чтение файла
        cout << "Файл " << filename << " успешно открыт" << endl;
        while (i < n) // пока не считали нужное количество чисел из файла
        {
            fin >> itmp;
            ::data.push_back(itmp); // пушим элементы в конец массива
            i++;
        }
    }
    catch (const exception& ex) // отлавливаем ошибки при открытии
    {
        cerr << ex.what() << endl;
        cout << "Ошибка открытия файла " << filename << endl;
        while (cin.get() != '\n');
        return 1;
    }

    fin.close(); // закрываем поток
    return 0;
}

//template <typename T>
int CreateFileC(std::string& filename, int * array, int n) // создание файла и запись в него данных
{
    ofstream fout;
    fout.exceptions(ofstream::badbit | ofstream::failbit);

    try
    {
        fout.open(filename);
        cout << "Файл " << filename << " успешно создан" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }


    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 10; j++, i++)
            fout << array[i] << " ";
        fout << endl;
    }

    fout.close();
    return 0;
}

int CreateFileVector(std::string& filename, vector<int> & array, int n) // создание файла и запись в него данных
{
    ofstream fout; // создаём поток на запись в файл
    fout.exceptions(ofstream::badbit | ofstream::failbit);

    try
    {
        fout.open(filename); // открываем поток
        cout << "Файл " << filename << " успешно создан" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }


    int i, j;
    for (i = 0; i < n;) // перебираем элементы массива
    {
        for (j = 0; j < 10; j++, i++) // после каждого десятого делаем перенос строки
            fout << array[i] << " ";
        fout << endl;
    }

    fout.close();
    return 0;
}
