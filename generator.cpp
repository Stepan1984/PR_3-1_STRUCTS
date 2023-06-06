#pragma once
#include "generator.h"

// количество повторений каждого элемента
#define R1 10
#define R2 100
#define R3 500
#define R4 1000

using namespace std;

int generator() 
{   
    vector<int> data_with_reps; // создаЄм массив, в котором будем хранить массив с новым набором данных
    int reps[4] = {R1, R2, R3, R4}; // количество повтор€ющихс€ элементов в массиве

    ReadFile(data_filenames[0], N4);

    for(int i = 0; i < 4; i++)
    {
        data_with_reps.clear(); // очистка массива
        CopyVectorData(data_with_reps, N4/reps[i], reps[i]); // N4 - количество элементов, reps[i] - количество повторений каждого элемента в массиве  
        ShuffleArray(data_with_reps, N4); // перемешиваем элементы массива
        CreateFileVector(data_filenames[i+1], data_with_reps, N4); // сохран€ем полученную последовательность в файл
    }
    return 0;
}
