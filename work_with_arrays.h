#pragma once
#include "include.h"
#include "global.h"

//template <typename T>
int CopyCData(int * array, int N, int r); // ����������� ������������ ���������� ��������� r ���
int CopyVectorData(std::vector<int> & array, int n, int r); // ����������� ������������ ���������� ��������� r ���
void ReverseArray(int* array, int N); // �������� �������
void ShuffleArray(std::vector<int> &array, int n); // ������������� ��������� �������
int random(std::mt19937_64& gen, int low, int high);
