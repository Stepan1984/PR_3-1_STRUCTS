#pragma once
// потоки
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // манипуляторы для форматного вывода
#include <thread> // параллельные потоки

//память
#include <malloc.h>  // free, allocate
#include <stdlib.h> // free

// типы, контейнеры
#include <string>
#include <vector>


// математика
#include <math.h>

// время
#include <chrono>

// язык
#include <locale.h>

// константы
#define N1 10000
#define N2 50000
#define N3 100000
#define N4 150000


inline std::string data_filenames[5] = { "test_numbers.txt","rep_10.txt","rep_100.txt","rep_500.txt","rep_1000.txt" }; // название обрабатываемых файлов
