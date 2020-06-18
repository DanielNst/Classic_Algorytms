// Algorytmi_Lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//





// 14. Указать множество вершин графа, доступных из заданной вершины на путях, веса которых не превышают заданной величины. Граф задан матрицей смежности. Все ребра имеют неотрицательный вес.
#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <locale.h>
#include <math.h>
#include <vector>
#include <array>
#include <queue>
#include <list>
#include <set>
#define inf 2147483647
using namespace std;

class link {
public:
	int number; 
	int key; 
	link(int new_number, int new_key) {
		number = new_number;
		key = new_key;
	}
};

class element {
public:
	int number;
	list<link*>* edges;
	element(int new_number) {
		number = new_number;
		edges = new list<link*>();
	}
};

class Graph {
public:
	list<element*>* Collection;
	Graph() {
		Collection = new list<element*>();
	}
	void Add() {
		element *tmp = new element(0);
		if (!Collection->empty())
			tmp->number = Collection->back()->number + 1;
		Collection->push_back(tmp);
	}
	void connectArc(int first, int second, int value) { //создание дуги first->second
		link *tmp = new link(second, value);
		for (auto const& i : *Collection)
			if (i->number == first)
				i->edges->push_back(tmp);
	}
	void Output() {
		for (auto const& i : *Collection) {
			cout << endl << "vertex: " << i->number;
			cout << " edges: ";
			for (auto const& k : *i->edges) {
				cout << k->number << " ";
			}
		}
	}
	int fromAdjacencyMatrix() { //создание графа из матрицы смежности
		vector<int> matrix;
		ifstream file;
		file.open("input.txt");
		matrix = read_ints(file);

		if (matrix.size() == 0) {
			cout << "File empty or doesn't exist" << endl;
			return 1;
		}
		if (sqrt(matrix.size()) != (long long)sqrt(matrix.size())) {
			cout << "Matrix is not square" << endl;
			return 1;
		}

		int size = sqrt(matrix.size());
		for (int i = 0; i < size; i++)
			Add();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (matrix.at(i*size + j))
					connectArc(i, j, matrix.at(i*size + j));
		return 0;
	}
	void findVertexes(int st_v, int max_len) {
		queue<int> all;
		set<int>* result = new set<int>();
		for (int i = 0; i < Collection->size(); i++) //Вносим все вершины графа в очередь
			if (i != st_v)
				all.push(i);
		while (!all.empty()) {
			Paths(st_v, all.front(), max_len, result); //Проверяем наличие пути в вершину из заданной вершины
			all.pop();
		}
		cout << endl;
		for (auto const& i : *result)
			cout << i << " ";
	}
	void Paths(int start, int destination, int max_len, set<int>* result) {
		bool *visited = new bool[Collection->size()];
		int *path = new int[Collection->size()];
		int path_index = 0;
		for (int i = 0; i < Collection->size(); i++) //Обозначаем все пути в графе  
			visited[i] = false;
		pathsUtil(start, destination, visited, path, path_index, max_len, result);

	}
private:
	void pathsUtil(int start, int destination, bool visited[], int path[], int &path_index, int max_len, set<int>* result) {
		// Помечаем текущую вершину и сохраняем в path[]
		visited[start] = true;
		path[path_index] = start;
		path_index++;
		//Если текущая вершина совпадает с назначением 
		int size = 0;
		if (start == destination) {
			for (int i = 0; i < path_index - 1; i++)
				for (auto const& v : *Collection)
					if (v->number == path[i])
						for (auto const& e : *v->edges)
							if (e->number == path[i + 1])
								size += e->key;
			if (size <= max_len)
				for (int i = 0; i < path_index; i++)
					if (result->find(path[i]) == result->end())
						result->insert(path[i]);
		}
		else {
			// Проверяем все вершины смежные с текущей вершиной
			for (auto const& i : *Collection)
				if (i->number == start)
					for (auto const& k : *i->edges)
						if (!visited[k->number])
							pathsUtil(k->number, destination, visited, path, path_index, max_len, result);
		}
		// Удаляем текущую вершину из path[] и помечаем как не посещённую
		path_index--;
		visited[start] = false;
	}
	vector<int> read_ints(istream& is) // Считывание из файла матрицы смежности
		{
			vector<int> result;
			copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(result));
			return result;
		}
};

int main(int argc, const char * argv[]) {
	Graph* my_graph = new Graph(); 
	if (my_graph->fromAdjacencyMatrix()) //Создаём граф из матрицы смежности и проверяем матрицу на пустоту и квадратность
		return 1;
	cout << endl << "Insert vertex: ";
	int starting_v;
	cin >> starting_v;
	cout << "Insert num: ";
	int max_len;
	cin >> max_len;
	cout << "Availiable vertexes:" << endl;
	my_graph->findVertexes(starting_v, max_len);
	return 0;
}
