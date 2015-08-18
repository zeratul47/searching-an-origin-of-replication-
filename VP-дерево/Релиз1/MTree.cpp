#include "MTree.h"

//метрика
int diffLetters(int a, int b){
	int count = 0;
	for (size_t i = 0; i < kmer; ++i)
		if(Gen[a+i] != Gen[b+i])
			++count;
	return count;
}

//среднее расстояние
double MedianDist(vector<int> &Table, size_t start, size_t end, int number){
	int s = 0;
	for(size_t i = start; i <= end; ++i){
		s += diffLetters(Table[i], Table[number]);
	}
	s /= (end-start+1);		//делил на table.size(), что не верно; +1 т.к. у нас условие <=
	return s;
}

//второй момент(дисперсия) (sum(x^2) - sum^2(x)/n)/(n-1)
double SecondMoment(vector<int> &Table, size_t start, size_t end, int p, double mu){
	if((end - start) != 0){		//дисперсия 1 элемента = 0(?)
		double s = 0;
		double s2 = 0;
		for(size_t i = start; i <= end; ++i){
			double temp = diffLetters(Table[i], Table[p]) - mu;
			s += temp;
			s2 += temp * temp;
		}
		return (s2-(s*s)/(end-start+1))/(end-start);
	}
	else
		return 0;
}

//выбо опорной точки
int Select_vp(vector<int> &Table, size_t start, size_t end, int &index){
	size_t p1 = rand() % (end-start) + start;
	size_t p2 = rand() % (end-start) + start;
	if (p1 > p2){
		size_t temp = p1;
		p1 = p2;
		p2 = temp;
	}
	int best_p = 0;
	double best_spread = 0;
	for(size_t i = p1; i <= p2; ++i){
		size_t d1;
		size_t d2;
		d1 = rand() % (end-start) + start;
		d2 = rand() % (end-start) + start;
		if (d1 > d2){
			size_t temp = d1;
			d1 = d2;
			d2 = temp;
		}
		double mu = MedianDist(Table, d1, d2, i);
		double spread = SecondMoment(Table, d1, d2, i, mu);
		if(spread >= best_spread){							//было > (если не исправили, то в тривиальном случае не находили бы элемент)
			best_spread = spread;
			best_p = i;
		}
	}
	index = best_p;
	return Table[best_p];
}

//построение дерева
MTreeNode* Make_vp_Tree(vector<int> &Table, size_t start, size_t end){
	if(start > end)		//при > был вылет за границы
		return NULL;
	if(start == end){
		MTreeNode* point = new MTreeNode;
		point->center = start;
		point->radius = 0;
		point->start = start;
		point->end = end;
		point->right = NULL;
		point->left = NULL;
		return point;
	}
	MTreeNode* point = new MTreeNode;
	int index;								//Table[index] == point->center
	point->center = Select_vp(Table, start, end, index);
	point->radius = MedianDist(Table, start, end, index);
	point->start = start;
	point->end = end;
	int i = start +1, j = end;

	// выносим в начало vp-точку (чтоб не сортировать)
	auto temp1 = Table[index];
	Table[index] = Table[start];
	Table[start] = temp1;

	//как в быстрой сортировке
	do {
		while (diffLetters(Table[i], point->center) <= point->radius) i++;
		while (diffLetters(Table[j], point->center) > point->radius) j--;	//здесь ошибки нет

		if(i <= j) {
			if (diffLetters(Table[i], point->center) > diffLetters(Table[j], point->center)){ 
				int temp = Table[i];
				Table[i] = Table[j];
				Table[j] = temp;
			}
			i++;
			j--;
		}
	} while (i < j);
	if (i == j)
		j--;

	size_t Lstart = start+1;
	size_t Lend = j;	
	size_t Rstart = i;
	size_t Rend = end;

	point->startR = Lstart;
	point->endR = Lend;

	if(point->radius <= 2){
		point->right = NULL;
		point->left = NULL;
		return point;
	}

	point->right = Make_vp_Tree(Table, Rstart, Rend);
	point->left = Make_vp_Tree(Table, Lstart, Lend);

	return point;
}

//сюда складываются все соседи
vector<int> FindP1;

//линейный поиск всех соседей
void LinearSearch(MTreeNode* root, int s, double radius, vector<int> &Table){
	for(int i = root->start; i <= root->end; ++i){
		if(diffLetters(Table[i], s) <= radius)
			FindP1[s] += 1;
	}
	return;
}

//поиск всех ближайших соседей
void search(MTreeNode* root, int s, double radius, vector<int> &Table){
	bool t = false;
	if(root != NULL){
		if ((diffLetters(root->center, s) - radius) <= root->radius){
			if (root->left != NULL){
				search(root->left, s, radius, Table);
			}
			else
				if(root->right == NULL)
					t = true;
		}
		if ((diffLetters(root->center, s) + radius) >= root->radius){
			if (root->right != NULL){
				search(root->right, s, radius, Table);
			}
			else
				if(root->left == NULL)
					t = true;
		}
		if(t)
			LinearSearch(root, s, radius, Table);
		else
			if(diffLetters(root->center, s) <= radius)
					FindP1[s] += 1;
	}
	return;
}

//поиск максимумов
vector<int> MaxPat(){
	vector<int> max;
	int max1 = FindP1[0];
	for(size_t i = 0; i < FindP1.size(); ++i)
		if (max1 < FindP1[i])
			max1 = FindP1[i];
	for(size_t i = 0; i < FindP1.size(); ++i)
		if (max1 == FindP1[i])
			max.push_back(i);
	return max;
}