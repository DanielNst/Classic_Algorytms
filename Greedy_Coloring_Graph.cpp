
#include "pch.h"
#include <iostream> 
#include <fstream>
#include <list> 
using namespace std;

class Graph
{
	int V;    // Число вершин
	list<int> *adj;    // Динамический массив матриц смежности
public: 
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph() { delete[] adj; }

	// добавление ребра графа
	void addEdge(int v, int w);

	// Основной метод графа
	void greedyColoring();

	void fileInput(Graph input_graph);
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  
}
void Graph::fileInput(Graph input_graph)
{
	ifstream file;
	file.open("input.txt");
	int first, second, edges_number;
	file >> edges_number;
	file >> edges_number;
	for (int j = 0; j < edges_number; j++)
	{
		file >> first;
		file >> second;
		cout << "First vertex:" << first << " ";
		cout << "Second vertex:" << second << endl;
		addEdge(first, second);

	}
	file.close();

}

void Graph::greedyColoring()
{
	int *result = new int [V];

	// Первой вершине - первый цвет 
	result[0] = 0;

	// Остальные V-1 вершины как неокрашенные
	for (int u = 1; u < V; u++)
		result[u] = -1;  // u не окрашена
	// Динамический массив для хранения цветов. True 
	// available[cr]  означает, что 
	// в цвет cr окашена смежная вершина
	bool *available = new bool [V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = false;
	// Окрашиваем оставшиеся V-1 вершину 
	for (int u = 1; u < V; u++)
	{
		// Посещаем все смежные вершины 
		// и отмечаем их как недоступные 
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (result[*i] != -1)
			{
				available[result[*i]] = true;
			}
		}
		// Ищем первый доступный цвет 
		int cr;
		for (cr = 0; cr < V; cr++)
		{
			if (available[cr] == false)
				break;
		}
		result[u] = cr; // Присваиваем найденный цвет
		// Сбрасываем значения до false для следующей итерации цикла
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{ 
			if (result[*i] != -1)
				available[result[*i]] = false;
			}
	}
	// Выводим результат окраски
	for (int u = 0; u < V; u++)
		cout << "Vertex " << u << " --->  Color "
		<< result[u] << endl;
}

int main()
{
	int vertexes_number;
	ifstream file;
	file.open("input.txt");
	file >> vertexes_number;
	file.close();
	Graph g1(vertexes_number);
	//g1.fileInput(g1);
	file.open("input.txt");
	int first, second, edges_number;
	file >> edges_number;
	file >> edges_number;
	for (int j = 0; j < edges_number; j++)
	{
		file >> first;
		file >> second;
		cout << "First vertex:" << first << " ";
		cout << "Second vertex:" << second << endl;
		g1.addEdge(first, second);

	}
	file.close();
	cout << "Coloring of graph 1 \n";
	g1.greedyColoring();
	return 0;
}

