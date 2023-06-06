#pragma once
#include "include.h"
#include "global.h"

//template <typename T>
int CopyCData(int * array, int N, int r); // копирование необходимого количества элементов r раз
int CopyVectorData(std::vector<int> & array, int n, int r); // копирование необходимого количества элементов r раз
void ReverseArray(int* array, int N); // разворот массива
void ShuffleArray(std::vector<int> &array, int n); // перемешивание элементов массива
int random(std::mt19937_64& gen, int low, int high);
