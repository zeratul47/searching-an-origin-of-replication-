#ifndef MTREE_H
#define MTREE_H

#include "Func.h"

struct MTreeNode{
	int center;
	double radius;
	int start, end;
	int startR, endR;
	MTreeNode* left;
	MTreeNode* right;
};

//метрика
int diffLetters(int a, int b);

//среднее расстояние
double MedianDist(vector<int> &Table, size_t start, size_t end, int number);

//построение дерева
MTreeNode* Make_vp_Tree(vector<int> &Table, size_t start, size_t end);

//поиск ближайшего соседа
void search(MTreeNode* root, int s, double radius, vector<int> &Table);

//нахождение всех максимумов
vector<int> MaxPat();

extern vector<int> FindP1;

#endif //MTREE_H