#pragma once
#include "work_with_arrays.h"

using namespace std;


int CopyCData(int * array, int n, int r) // копирование n элементов r раз из глобального массива
{
	if (::data.empty())
		return 0;

	int i, j;
	for(i = 0; i < r; i++) // считаем количество повторений фрагмента данных
	{
		for (j = 0; j < n; j++) // перебираем элементы массива
			array[j] = ::data[j];
	}
	return 1;
}

int CopyVectorData(vector<int> & array, int n, int r) // копирование n элементов r раз из глобального массива
{
	if (::data.empty())
		return 0;

	int i, j;
	for (i = 0; i < r; i++) // считаем количество повторений фрагмента данных
	{
		for (j = 0; j < n; j++) // перебираем элементы массива
			array.push_back(::data[j]);
	}
	return 1;
}

void ReverseArray(int* array, int N) // функция разворота массива
{
	int itmp, half = N / 2;
	for (int i = 0, j = N - 1; i < half; i++, j--)
	{
		itmp = array[i];
		array[i] = array[j];
		array[j] = itmp;
	}
}

void ShuffleArray(vector<int> &array, int n) // перемешивание элементов массива
{
	random_device rd; // генератор случайных значений
	mt19937_64 gen(rd());
	int i;
	for(i = 0; i < n; i++)
		swap(array[i], array[random(gen, 0, n - 1)]);
}

int random(mt19937_64 &gen, int low, int high)
{
	uniform_int_distribution<> dist(low, high);
	return dist(gen);
}