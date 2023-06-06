#pragma once
#include "generator.h"

// ���������� ���������� ������� ��������
#define R1 10
#define R2 100
#define R3 500
#define R4 1000

using namespace std;

int generator() 
{   
    vector<int> data_with_reps; // ������ ������, � ������� ����� ������� ������ � ����� ������� ������
    int reps[4] = {R1, R2, R3, R4}; // ���������� ������������� ��������� � �������

    ReadFile(data_filenames[0], N4);

    for(int i = 0; i < 4; i++)
    {
        data_with_reps.clear(); // ������� �������
        CopyVectorData(data_with_reps, N4/reps[i], reps[i]); // N4 - ���������� ���������, reps[i] - ���������� ���������� ������� �������� � �������  
        ShuffleArray(data_with_reps, N4); // ������������ �������� �������
        CreateFileVector(data_filenames[i+1], data_with_reps, N4); // ��������� ���������� ������������������ � ����
    }
    return 0;
}
