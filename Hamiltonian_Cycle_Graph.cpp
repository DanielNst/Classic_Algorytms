
/* C++ program for solution of Hamiltonian
Cycle problem using backtracking */

#include "pch.h"
#include <iostream> 
#include <array>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;
void printSolution(int path[],int s);
bool isSafe(int v, int s, vector<int> graph,int path[], int pos) // Проверяем, можно ли добавить текущую вершину к существущему Гамильтонову циклу в path[]
{
	if (graph.at(path[pos-1] * s + v) == 0) // Проверяем, является ли данная вершина смежной с предыдущей добавленной
		return false;

	for (int i = 0; i < pos; i++) // Проверяем наличие данной вершины в уже добавленных в цикл
		if (path[i] == v)
			return false;

	return true;
}

bool hamCycleUtil(int s, vector<int> graph,int path[], int pos) // Основная рекурсивная функция для поиска гамильтонова цикла
{
	if (pos == s) // Если все вершины добавлены в гамильтонов цикл
	{
		if (graph.at(path[pos - 1] * s + path[0]) == 1) // И если есть ребро от последней добавленной вершины к первой
			return true;
		else
			return false;
	}
	for (int v = 1; v < s; v++) //Пробуем различные вершины на добавление в Гамильтонов цикл, не используем нулевую, так как с неё начинаем гамильтонов цикл
	{
		if (isSafe(v,s, graph, path, pos)) // Проверяем можно ли добавить эту вершину в гамильтонов цикл
		{
			path[pos] = v;
			if (hamCycleUtil(s, graph, path, pos + 1) == true) // Возвращаемся к дальнейшей постройке цикла
				return true;
			path[pos] = -1; // Если данная вершина не подходит к решению, удаляем её из гамильтонова цикла
		}
	}
	return false; // Если ни одна вершина не может быть добавлена в гамильтонов цикл, то выходим из подпрограммы
}



bool hamCycle(int s, vector<int> graph) // Основная функция подпрограммы 
{
	int *path = new int[s];
	for (int i = 0; i < s; i++)
		path[i] = -1;
	path[0] = 0; //Выбираем нулевую вершину как стартовую, так как в случае если есть гамильтонов цикл, можно выбрать любую вершину в неориентированном графе
	if (hamCycleUtil(s, graph, path, 1) == false)
		{	
			cout << "\nSolution does not exist";
			return false;
		}

	printSolution(path,s);
	return true;
}
void printSolution(int path[], int s) // Вывод гамильтонова цикла
{
	cout << "Solution Exists:"
		" Following is one Hamiltonian Cycle \n";
	for (int i = 0; i < s; i++)
		cout << path[i] << " ";
	cout << path[0] << " ";
	cout << endl;
}
vector<int> read_ints(istream& is) {
	vector<int> result;
	copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(result));
	return result;
}

int fromFile(vector<int> &matrix) { //создание графа из матрицы смежности
	ifstream file;
	file.open("input.txt");
	matrix = read_ints(file);

	if (matrix.size() == 0) {
		cout << "File is empty or doesn't exist" << endl;
		return 1;
	}
	if (sqrt(matrix.size()) != (long long)sqrt(matrix.size())) {
		cout << "Matrix isn't square" << endl;
		return 1;
	}

	return 0;
}
int main()
{
	vector<int> matrix;
	fromFile(matrix);
	int s = sqrt(matrix.size());
	hamCycle(s,matrix);
	return 0;
}


