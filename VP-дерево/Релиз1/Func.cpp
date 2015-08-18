#include "Func.h"

string Gen;
size_t GenSize;
size_t kmer;

//получение участка из файла
string GetFromFile(string filename){
	ifstream fin(filename);
	string Gen, temp;
	getline(fin, temp);
	Gen = Gen + temp;
	temp.clear();
    while(fin){
		getline(fin, temp);
		Gen = Gen + temp;
    }
	fin.close();
    return Gen;
}

//комплиментарный разворот
string KompReverse(string gen){
	replace(gen.begin(), gen.end(), 'A', '1');
	replace(gen.begin(), gen.end(), 'G', '2');
	replace(gen.begin(), gen.end(), 'T', 'A');
	replace(gen.begin(), gen.end(), '1', 'T');
	replace(gen.begin(), gen.end(), 'C', 'G');
	replace(gen.begin(), gen.end(), '2', 'C');
	reverse(gen.begin(), gen.end());
	return gen;
}

//строим таблицу слов длиной kmer
vector<int> WordTable(string &gen){
	vector<int> SetGen (2*(GenSize - kmer+1));
	size_t length = GenSize - kmer+1;
	for(size_t i = 0; i < length; ++i){
		SetGen[i] = i;
		SetGen[i+length] = i+GenSize;
	}
	return SetGen;
}
