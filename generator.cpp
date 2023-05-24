#pragma once
#include "preproc.h"
#include "generator.h"

// количество повторений каждого элемента
#define R1 10
#define R2 100
#define R3 500
#define R4 1000

using namespace std;

int generator() 
{   
 
    int reps[4] = {R1, R2, R3, R4}; // количество повтор€ющихс€ элементов в массиве

    thread thr1(FillFile, std::ref(data_filenames[2]), reps[1], N4);
    thread thr2(FillFile, std::ref(data_filenames[3]), reps[2], N4);
    thread thr3(FillFile, std::ref(data_filenames[4]), reps[3], N4);

    FillFile(data_filenames[1], reps[0], N4);

    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}

int FillFile(std::string& filename, int reps, int amount)
{
    ifstream fin;
    ofstream fout;
    fin.exceptions(ifstream::badbit | ifstream::failbit);
    fout.exceptions(ofstream::badbit | ofstream::failbit);
    
    try
    {
        fin.open("test_numbers.txt");
        cout << "‘айл успешно открыт" << endl;
        fout.open(filename);
        cout << "‘айл успешно создан" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        fin.close();
        fout.close();
        return 1;
    }
    
    int i = 0, j;
    string stmp;
    while (i < amount)
    {
        getline(fin, stmp); // считываем строку из файла
        for (j = 0; j < reps; j++)
        {
            fout << stmp << endl;
        }
        i += reps * 10;
    }
    
    fout.close();
    fin.close();
    return 0;
}


