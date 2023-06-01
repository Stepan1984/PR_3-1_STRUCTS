#pragma once
#include "generator.h"
#include "preproc.h"

using namespace std;

/* вспомогательные функции */
int ReadFile(string & filename,vector<int> &array, int n); // чтение файла
int CopyData(vector<int> &data, int * array, int N); // копирование необходимого количества элементов
void ReverseArray(int * array, int N); // разворот массива

/* алгоритмы сортировки */
void BubbleSort (int *a, int n, ofstream &fout); // сортировка пузырьком
void ShakerSort (int *a, int n, ofstream &fout);  // шейкерная сортировка
void NonRecursiveQuickSort (int *a, int n, ofstream &fout); // быстрая сортировка (нерекурсивная)
void NaturalMergeSort(int *a, int n, ofstream &fout); // сортировка естественным слиянием



/* Вспомогательные функции */
int main()
{
    setlocale(LC_ALL, "Rus"); 
	int a, s, i, l; // итераторы
	string result_filenames[4] = { "Bubble.txt","Shaker.txt", "Quick.txt","Merge.txt" }; // названия файлов для сохранения результата работы алгоритмов
	int amounts[4] = {N1, N2, N3, N4}, N; // массив с необходимыми количествами эл-ов в массивах // количество эл-ов в данном массиве
	int array[N4]; // сортируемый массив
    void (*f[])(int *, int, ofstream &) = {BubbleSort, ShakerSort, NonRecursiveQuickSort , NaturalMergeSort }; // массив указателей на функции
	vector<int> data; // массив с исходными элементами
	string table_header = "    время нс.   |    основные    | второстепенные | память | тыс. |  изначально   \n"; // 16|16|16|8|6|15

	generator(); // создаём файлы с повторяющимися элементами

	ofstream* files = new ofstream[4];
  	for (int i = 0; i < 4; i++)
    	files[i].exceptions(ofstream::badbit | ofstream::failbit);

	try
	{ // создаём файлы для хранения времени работы сортировок
		for(i = 0; i < 4; i++)
		{
			files[i].open(result_filenames[i].c_str());
			files[i] << table_header;
		}
		
	}
	catch(const exception& ex)
	{
		cerr << ex.what() << endl;
		std::cout << "Ошибка открытия файла " << result_filenames[i] << endl << "ENTER";
		while(cin.get() != '\n');
		return 101;
	}

	

	for(l = 0; l < 5; l++) // перебираем обрабатываемые файлы
	{
		if (ReadFile(data_filenames[l], data, N4)) // считываем необходимое количество чисел из файла
		{
			std::cout << "ENTER" << endl;
			while (cin.get() != '\n');
			return 101;
		}

		for (s = 0; s < 4; s++) // перебор размеров массива
		{
			N = amounts[s]; // запоминаем количество эл-ов в нынешнем массиве
			for (a = 0; a < 4; a++) // перебор алгоритмов сортировки
			{
				CopyData(data, array, N); // копируем данные в массив

				// если массив не отсортирован
				f[a](array, N, files[a]); // сортируем массив
				files[a] << "|" << setw(15) << left << "не отсортирован" << endl;

				// если массив отсортирован
				f[a](array, N, files[a]); // сортируем массив
				files[a] << "|" << setw(15) << left << "отсортирован" << endl;

				// если массив отсортирован, но нужно его развернуть
				ReverseArray(array, N); // разворачиваем массив
				f[a](array, N, files[a]); // сортируем массив
				files[a] << "|" << setw(15) << left << "развёрнут" << endl;

			}
		}
	}

	for( i = 0; i < 4; i++)
		files[i].close();

	delete[] files;

    return 1;
}

int ReadFile(string & filename,vector<int> &array, int n) // функция чтения файла
{
    int i = 0, itmp;
    ifstream fin; // создаём поток
    fin.exceptions(ifstream::badbit | ifstream::failbit); // для обработки исключительных ситуаций при открытие
    try
    {
        fin.open(filename); // открываем поток на чтение файла
        cout << "Файл " << filename << " успешно открыт" << endl;
		while(i < n) // пока не считали нужное количество чисел из файла
		{
			fin >> itmp; 
			array.push_back(itmp); // пушим элементы в конец массива
			i++;
		}
    }
    catch(const exception& ex) // отлавливаем ошибки при открытии
    {
        cerr << ex.what() << endl;
        cout << "Ошибка открытия файла " << filename << endl;
        while(cin.get() != '\n');
		return 1;
    }

    fin.close(); // закрываем поток
	return 0;
}

int CopyData(vector<int> &data, int * array, int N)
{
	if(data.empty())
		return 0;

	int i = 0;
	while(i < N)
	{
		array[i] = data[i];
		i++;
	}
	return 1;
}

void ReverseArray(int * array, int N) // функция разворота массива
{
	int itmp, half = N / 2;
	for(int i = 0, j = N - 1; i < half; i++, j--)
	{
		itmp = array[i];
		array[i] = array[j];
		array[j] = itmp;
	}
}


/* Алгоритмы сортировки */
void BubbleSort (int *a, int n, ofstream &fout) // сортировка пузырьком
{
	long unsigned int mainC = 0, secondaryC = 0, memory = 0; // mainCompares // secondaryCompares
	int i, j, itmp; memory += 3 * sizeof(int); 
	chrono::steady_clock::time_point start_time, end_time; // переменные для подсчёта времени работы алгоритма
    start_time = chrono::steady_clock::now();
	for (i = 1; ++secondaryC && i < n; i++) // проход по всему массиву
		for (j = n - 1; ++secondaryC && j >= i; j--) // проход по массиву с конца до i (в том числе проверим (i-1) элемент)
			if (++mainC && a[j-1] > a[j])
			{
				itmp = a[j-1];
				a[j-1] = a[j];
				a[j] = itmp;
			}
	end_time = chrono::steady_clock::now();
	fout << setw(16) << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "|" 
		<< setw(16) << mainC << "|" << setw(16) << secondaryC << "|" << setw(8) << memory << "|" << setw(6) << n/1000;
}

void ShakerSort (int *a, int n, ofstream &fout)
{
	unsigned long int mainC = 0, secondaryC = 0, memory = 0; 
	int j, k = n-1, left = 1, right = n-1, x; memory += 5*sizeof(int);
	/*
	left, right - границы неотсортированного интервала
	k - индекс последнего, установленного в нужную позицию элемента
	*/
	chrono::steady_clock::time_point start_time, end_time; // переменные для подсчёта времени работы алгоритма
    start_time = chrono::steady_clock::now();
	do
	{
		for (j=right; ++secondaryC && j >= left; j--)	//сначала просматриваем справа налево
			if (++mainC && a[j-1] > a[j])
			{
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
				k = j;
			}
		left = k + 1;
		for (j = left; ++secondaryC && j <= right; j++)	//а теперь просматриваем слева направо
			if (++mainC && a[j-1] > a[j])
			{
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
				k = j;
			}
		right = k-1;
	}while(++secondaryC && left <= right);	//и так до тех пор, пока есть что просматривать
	end_time = chrono::steady_clock::now();
fout << setw(16) << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "|" 
		<< setw(16) << mainC << "|" << setw(16) << secondaryC << "|" << setw(8) << memory << "|" << setw(6) << n/1000;
}

void NonRecursiveQuickSort (int *a, int n, ofstream &fout)
{
	unsigned long int mainC = 0, secondaryC = 0, memory = 0;

	const int M=log(n)/log(2)+1;
	int i, j, left, right, s, x, w; memory += 8 * sizeof(int);
	struct stack {int left, right;} *stack;
	stack = (struct stack *) malloc (M*sizeof(struct stack)); memory += M * sizeof(struct stack);
	s = 0;
	stack[0].left = 0;
	stack[0].right = n-1;

	chrono::steady_clock::time_point start_time, end_time; // переменные для подсчёта времени работы алгоритма
    start_time = chrono::steady_clock::now();

	do 				//выбор из стека последнего запроса
	{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		do			//разделение а[left]… a[right]
		{
			i = left; j = right;
			x = a[(left+right)/2];
			do
			{
				while (++mainC && a[i]<x) i++; 
				while (++mainC && x<a[j]) j--; 
				if (++secondaryC && i<=j) // проверяем индексы
				{
					w = a[i]; a[i] = a[j]; a[j] = w;
					i++; j--;
				}
			}
			while (++secondaryC && i<j);
			if (++secondaryC && i<right && ++secondaryC && right-i>=j-left)     //если правая часть не меньше левой
			{                                   //запись в стек границ правой части
				s++;
				stack[s].left = i;
				stack[s].right = right;
				right = j;      //теперь left и right ограничивают левую часть
			}
			else if (++secondaryC && j>left && ++secondaryC && j-left>right-i )   //если левая часть больше правой
			{                                    //запись в стек границ левой части
				s++;
				stack[s].left = left;
				stack[s].right = j;
				left = i;      //теперь left и right ограничивают правую часть
			}
			else left = right;     //делить больше нечего, интервал "схлопывается"

		}while (++secondaryC && left<right);

	}while (++secondaryC && s>-1);
	end_time = chrono::steady_clock::now();
	free (stack);
	fout << setw(16) << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "|" 
		<< setw(16) << mainC << "|" << setw(16) << secondaryC << "|" << setw(8) << memory << "|" << setw(6) << n/1000;
}

void NaturalMergeSort(int *a, int n, ofstream &fout)
{
	unsigned long int mainC = 0, secondaryC = 0, memory = 0;

    int split;                   // индекс, по которому делим массив
    int end, *p=a, *tmp; memory += 2 * sizeof(int*);
    char flag = 0, sorted = 0; memory += 2 * sizeof(char);
    int pos1, pos2, pos3; memory += 5 * sizeof(int);
    tmp = (int*) malloc (n*sizeof(int)); memory += n * sizeof(int);

	chrono::steady_clock::time_point start_time, end_time; // переменные для подсчёта времени работы алгоритма
    start_time = chrono::steady_clock::now();

    do                 // если есть более 1 элемента
    {
        end = n; pos2 = pos3 = 0;
        do
        {
            p += pos2; end = n - pos3;
            for (split=1; ++secondaryC && split < end && ++mainC && p[split-1] <= p[split]; split++); //первая серия
            if (++secondaryC && split == n) 
				{sorted = 1 ; break;}
            pos1 = 0; pos2 = split;
            while (++secondaryC && pos1 < split && ++secondaryC && pos2 < end ) 	// идет слияние, пока есть хоть один элемент в каждой серии
            {
				
                if (++mainC && p[pos1] < p[pos2])
                    tmp[pos3++] = p[pos1++];
                else
                {
                    tmp[pos3++] = p[pos2++];
                    if (++mainC && p[pos2] < p[pos2-1]) break;
                }
            }
            // одна последовательность закончилась - копировать остаток другой в конец буфера
            while (++secondaryC && pos2 < end && ++mainC && tmp[pos3-1]<=p[pos2] )  			 // пока вторая последовательность не пуста
                tmp[pos3++] = p[pos2++];
            while ( ++secondaryC && pos1 < split )  		// пока первая последовательность не пуста
                tmp[pos3++] = p[pos1++];
        }
        while (++secondaryC && pos3 < n );
        if (sorted) break;
        p = tmp;
        tmp = a;
        a = p;
        flag = !flag;
    }
    while (++secondaryC && split<n);
    if (flag)
    {
        for (pos1 = 0; ++secondaryC && pos1 < n; pos1++)
            tmp[pos1] = a[pos1];
        free (a);
    }
    else
        free (tmp);
	
	end_time = chrono::steady_clock::now();
	fout << setw(16) << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "|" 
		<< setw(16) << mainC << "|" << setw(16) << secondaryC << "|" << setw(8) << memory << "|" << setw(6) << n/1000; 

	/*cout << setw(16) << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << endl;*/
}