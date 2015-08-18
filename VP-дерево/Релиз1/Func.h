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

//получение участка из файла
string GetFromFile(string filename);

//комплиментарный разворот
string KompReverse(string gen);

//строим таблицу слов длиной kmer
vector<int> WordTable(string& gen);

#endif //FUNC_H