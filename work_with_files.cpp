#pragma once
#include "work_with_files.h"


using namespace std;

int ReadFile(string& filename, int n) // ������� ������ �����
{
    int i = 0, itmp;
    ifstream fin; // ������ �����
    fin.exceptions(ifstream::badbit | ifstream::failbit); // ��� ��������� �������������� �������� ��� ��������
    try
    {
        fin.open(filename); // ��������� ����� �� ������ �����
        cout << "���� " << filename << " ������� ������" << endl;
        while (i < n) // ���� �� ������� ������ ���������� ����� �� �����
        {
            fin >> itmp;
            ::data.push_back(itmp); // ����� �������� � ����� �������
            i++;
        }
    }
    catch (const exception& ex) // ����������� ������ ��� ��������
    {
        cerr << ex.what() << endl;
        cout << "������ �������� ����� " << filename << endl;
        while (cin.get() != '\n');
        return 1;
    }

    fin.close(); // ��������� �����
    return 0;
}

//template <typename T>
int CreateFileC(std::string& filename, int * array, int n) // �������� ����� � ������ � ���� ������
{
    ofstream fout;
    fout.exceptions(ofstream::badbit | ofstream::failbit);

    try
    {
        fout.open(filename);
        cout << "���� " << filename << " ������� ������" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }


    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 10; j++, i++)
            fout << array[i] << " ";
        fout << endl;
    }

    fout.close();
    return 0;
}

int CreateFileVector(std::string& filename, vector<int> & array, int n) // �������� ����� � ������ � ���� ������
{
    ofstream fout; // ������ ����� �� ������ � ����
    fout.exceptions(ofstream::badbit | ofstream::failbit);

    try
    {
        fout.open(filename); // ��������� �����
        cout << "���� " << filename << " ������� ������" << endl;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }


    int i, j;
    for (i = 0; i < n;) // ���������� �������� �������
    {
        for (j = 0; j < 10; j++, i++) // ����� ������� �������� ������ ������� ������
            fout << array[i] << " ";
        fout << endl;
    }

    fout.close();
    return 0;
}
