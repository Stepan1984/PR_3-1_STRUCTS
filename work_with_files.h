#pragma once
#include "include.h"
#include "global.h"


int ReadFile(std::string& filename, int n); // ������ �����

//template <typename T>
int CreateFileC(std::string& filename, int * array , int n); // �������� ����� � ������ � ���� ������
int CreateFileVector(std::string& filename, std::vector<int> & array, int n); // �������� ����� � ������ � ���� ������
