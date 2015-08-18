#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

extern string Gen, RKGen;
extern size_t GenSize;
extern size_t kmer;

//��������� ������� �� �����
string GetFromFile(string filename);

//��������������� ��������
string KompReverse(string gen);

//������ ������� ���� ������ kmer
vector<int> WordTable(string& gen);

#endif //FUNC_H