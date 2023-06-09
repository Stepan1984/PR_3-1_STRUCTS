#pragma once
#include "include.h"
#include "generator.h"
#include "work_with_arrays.h"
#include "work_with_files.h"
#include "global.h"


using namespace std;

/* алгоритмы сортировки */
void BubbleSort (int *a, int n, ofstream &fout); // сортировка пузырьком
void ShakerSort (int *a, int n, ofstream &fout);  // шейкерная сортировка
void NonRecursiveQuickSort (int *a, int n, ofstream &fout); // быстрая сортировка (нерекурсивная)
void NaturalMergeSort(int *a, int n, ofstream &fout); // сортировка естественным слиянием



int main()
{
    setlocale(LC_ALL, "Rus"); 
	int a, s, i, l; // итераторы
	string result_filenames[4] = { "Bubble.txt","Shaker.txt", "Quick.txt","Merge.txt" }; // названия файлов для сохранения результата работы алгоритмов
	int amounts[4] = {N1, N2, N3, N4}, N; // массив с необходимыми количествами эл-ов в массивах // количество эл-ов в данном массиве
	int array[N4]; // сортируемый массив
    void (*f[])(int *, int, ofstream &) = {BubbleSort, ShakerSort, NonRecursiveQuickSort , NaturalMergeSort }; // массив указателей на функции
	string table_header = "    время нс.   |    основные    | второстепенные | память | тыс. |  изначально   \n"; // 16|16|16|8|6|15

	generator(); // создаём файлы с повторяющимися элементами

	ofstream* files = new ofstream[4]; // создаём массив потоков на запись в файлы
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
		::data.clear(); // очищаем массив от старого набора данных
		if (ReadFile(data_filenames[l], N4)) // считываем необходимое количество чисел из файла
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
				CopyCData(array, N, 1); // копируем данные в массив

				// массив не отсортирован
				f[a](array, N, files[a]); // сортируем массив
				files[a] << "|" << setw(15) << left << "не отсортирован" << endl;

				// массив отсортирован
				f[a](array, N, files[a]); // сортируем массив
				files[a] << "|" << setw(15) << left << "отсортирован" << endl;

				// массив отсортирован, но нужно его развернуть
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

/* Алгоритмы сортировки */
void BubbleSort (int *a, int n, ofstream &fout) // сортировка пузырьком
{
	long long unsigned int mainC = 0, secondaryC = 0, memory = 0; // mainCompares // secondaryCompares
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
	unsigned long long int mainC = 0, secondaryC = 0, memory = 0; 
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
	unsigned long long int mainC = 0, secondaryC = 0, memory = 0;

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
	unsigned long long int mainC = 0, secondaryC = 0, memory = 0;

    int split; // индекс, по которому делим массив
    int end, *p=a, *tmp; memory += 2 * sizeof(int*);
    char flag = 0, sorted = 0; memory += 2 * sizeof(char);
    int pos1, pos2, pos3; memory += 5 * sizeof(int);
    tmp = (int*) malloc (n*sizeof(int)); memory += n * sizeof(int);

	/*
	pos1 - начало первой части (сортируемой в current итерации)
	pos2 - сдвиг относительно начала массива для определения левой границы части, неотсортированной в предыдущей итерации цикла
	pos3 - индекс последнего добавленного в новый массив элемента
	*/


	chrono::steady_clock::time_point start_time, end_time; // переменные для подсчёта времени работы алгоритма
    start_time = chrono::steady_clock::now();

	// цикл пока массив разделён на части
    do 
    {
		// возвращаем переменные к исходным значениям
        end = n; // конец массива
		pos2 = pos3 = 0; 

		//
        do
        {
            p += pos2; // p (указатель на начало сортируемой части) сдвигаем вправо на pos2 элементов 
			end = n - pos3; // индекс конца массива уменьшаем на pos3 элементов, получая конец сортируемой части
			// неотсортированная часть начинается с указателся p и заканчивается на индексе end, относительно p

			// цикл поиска упорядоченных последовательностей внутри неотсортированной части
            for (split = 1; ++secondaryC && split < end && ++mainC && p[split-1] <= p[split]; split++); //первая часть // пока предыдущий элемент <= нынешнему, увеличиваем размер первой части сдвигая split вправо 

            if (++secondaryC && split == n) // если размер части равен длине массива
				{sorted = 1 ; break;} // выходим из всех циклов, массив отсортирован 

			// если длина первой части < размера массива (т.е. массив не отсортирован)
            pos1 = 0; pos2 = split; // устанавливаем индексы начала первой и второй части 
			// 1-часть:[pos1;split]  
			// 2-часть:[pos2;end] или [split;end]



			// цикл слияния и записи в новый массив
            while (++secondaryC && pos1 < split && ++secondaryC && pos2 < end ) // идет слияние, пока есть хоть один элемент в каждой серии
            {
				
                if (++mainC && p[pos1] < p[pos2]) // если элемент из первой серии меньше элемента из второй
                    tmp[pos3++] = p[pos1++]; // в новый массив записываем элемент из первой серии и в проходе по первой серии переходим к следующему элементу
                else // если элемент из второй серии меньше элемента из первой
                {
                    tmp[pos3++] = p[pos2++]; // в новый массив записываем элемент из второй серии и во 2-серии переходим к следующему элементу
                    if (++mainC && p[pos2] < p[pos2-1]) break; // если элемент из 2-серии меньше чем стоящий перед ним элемент, то выходим из цикла слияния, так как если мы добавим число в новый массив, то оно будет меньше предыдущего в нём, то есть пропадает смысл сортировки по возрастанию
                } 
            }


            // все элементы одной из частей закончились => копируем оставшиеся элементы из второй части в конец нового массива
            while (++secondaryC && pos2 < end && ++mainC && tmp[pos3-1]<=p[pos2] ) // пока вторая последовательность не пуста // pos3(индекс в tmp массиве) // пока элемент во новом массиве меньше или равен элементу из старого
                tmp[pos3++] = p[pos2++]; // копируем значение в новый массив из старого и переходим к следующим элементам
            while ( ++secondaryC && pos1 < split ) // пока первая последовательность не пуста
                tmp[pos3++] = p[pos1++]; // копируем в новый из старого без сравнения
        }
        while (++secondaryC && pos3 < n ); // пока индекс конца отсортированной части меньше длины массива, то есть пока массив не заполнен отсортированными фрагментами


        if (++secondaryC && sorted) break; // если массив отсортирован
        p = tmp; // массивом для сортировки делаем тот, в который только что копировали данные
        tmp = a; //...
        a = p; //...
        flag = !flag; // флаг меняет значение (для того чтобы знать в каком из массивов хранится сортируемый/отсортированный массив)
    }
    while (++secondaryC && split < n); // пока индекс разделителя меньше длины массива


    if (++secondaryC && flag) // проверка местоположения отсортированного массива
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
}