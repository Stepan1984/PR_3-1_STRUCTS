#pragma once
#include "work_with_arrays.h"

using namespace std;


int CopyCData(int * array, int n, int r) // ����������� n ��������� r ��� �� ����������� �������
{
	if (::data.empty())
		return 0;

	int i, j;
	for(i = 0; i < r; i++) // ������� ���������� ���������� ��������� ������
	{
		for (j = 0; j < n; j++) // ���������� �������� �������
			array[j] = ::data[j];
	}
	return 1;
}

int CopyVectorData(vector<int> & array, int n, int r) // ����������� n ��������� r ��� �� ����������� �������
{
	if (::data.empty())
		return 0;

	int i, j;
	for (i = 0; i < r; i++) // ������� ���������� ���������� ��������� ������
	{
		for (j = 0; j < n; j++) // ���������� �������� �������
			array.push_back(::data[j]);
	}
	return 1;
}

void ReverseArray(int* array, int N) // ������� ��������� �������
{
	int itmp, half = N / 2;
	for (int i = 0, j = N - 1; i < half; i++, j--)
	{
		itmp = array[i];
		array[i] = array[j];
		array[j] = itmp;
	}
}

void ShuffleArray(vector<int> &array, int n) // ������������� ��������� �������
{
	random_device rd; // ��������� ��������� ��������
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