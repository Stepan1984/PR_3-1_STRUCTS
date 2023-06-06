#pragma once
#include "include.h"
#include "global.h"


int ReadFile(std::string& filename, int n); // чтение файла

//template <typename T>
int CreateFileC(std::string& filename, int * array , int n); // создание файла и запись в него данных
int CreateFileVector(std::string& filename, std::vector<int> & array, int n); // создание файла и запись в него данных
