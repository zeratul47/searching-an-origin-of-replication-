#include "MTree.h"
#include <ctime>
#include <chrono>


int main(){
	srand( time( 0 ) );
	kmer = 9;								//варируемое значение (длина)
	int d = 1;								//количество замен

	string filename = "ProbOriC1.txt";
	cout << "Enter dataset file name: ";
	cin >> filename;

	cout << "Enter length of kmer: ";
	cin >> kmer;
	cout << "Enter number of missmatches: ";
	cin >> d;
	d = 1;

	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

	Gen = GetFromFile(filename);		//получаем участок из файла
	GenSize = Gen.size();					//√лобальна€ переменна€ - длина полученного участка
	Gen += KompReverse(Gen);				//комплементарный разворот

	vector<int> Table = WordTable(Gen);		//разбиваем наши строки (формально строку) на паттеры длиной kmer
	FindP1.resize(Gen.size(), 0);

	MTreeNode* root = Make_vp_Tree(Table, 0, Table.size()-1);			//строим дерево (важно передать индекс последнего элемента!! т.к. все циклы <=)

	for(size_t i = 0; i < Table.size(); ++i){		//¬ыполн€ем поиск
		search(root, Table[i], d, Table);
	}

	vector<int> maxp = MaxPat();
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	std::cout << "elapsed time: " << elapsed_seconds/1000.0 << "s\n";

	ofstream fout("result.txt");
	if(!maxp.empty())
		if(FindP1[maxp[0]] <=10 && FindP1[maxp[0]] >= 2)
			for (size_t i = 0; i < maxp.size(); ++i){			//вывод результатов
				for(size_t j = maxp[i]; j < maxp[i]+kmer; ++j){
					cout << Gen[j];
					fout << Gen[j];
				}
				cout << "  " << FindP1[maxp[i]] << endl;
				fout << "  " << FindP1[maxp[i]] << endl;
			}
		else
			cout << "DNA-box are not found" << endl;
	else
		cout << "DNA-box are not found" << endl;
	fout.close();

	system("pause");
	return 0;
}