#include "pch.h"
#include <iostream>
#include <fstream>
#include <stack>


using namespace std;

ifstream inpFile("input.txt");		//Файл входных данных
ofstream outFile("output.txt");		//Выходной файл с результатом работы программы

class Graph {
	int BaseRange;	 // Дальность передачи станции
	int CountVertex; // Количество вершин в графе 
	int **adjMatrix; // Массив списков смежных вершин 

public:
	Graph(int countVertex) {
		this->CountVertex = countVertex;
		BaseRange = INT_MAX;
		adjMatrix = new int*[countVertex];

		for (int i = 0; i < CountVertex; i++) {
			adjMatrix[i] = new int[CountVertex];
		}
	}

	// Установка дальности передачи
	void setBaseRange(int range) {
		BaseRange = range;
	}

	//Добавление вершины в матрицу смежности
	void addEdge(int u, int v, int weight) {
		adjMatrix[u][v] = weight;
	}

	//Печать матрицы смежности
	void printMatrix() {
		cout << "Adjacency matrix" << endl;
		outFile << "Adjacency matrix" << endl;
		for (int i = 0; i < CountVertex; i++) {
			for (int j = 0; j < CountVertex; j++) {
				cout.width(2);
				cout << adjMatrix[i][j] << "  ";
				outFile << adjMatrix[i][j] << "  ";
			}
			cout << endl;
			outFile << endl;
		}
	}

	//Поиск вершины с максимальной степенью
	int findMaxDegreeVertex(int **matrix, bool *isCovered) {
		int vertex = INT_MAX;
		int maxCount = 0;

		for (int i = 0; i < CountVertex; i++) {
			int count = 0;
			for (int j = 0; j < CountVertex; j++) {
				if (matrix[i][j] != 0 && matrix[i][j] <= BaseRange && !isCovered[j]) {
					count++;
				}
			}
			if (count > maxCount) {
				vertex = i;
				maxCount = count;
			}
		}

		return vertex;
	}

	// Нахождение вершинного покрытия
	void findVertexCover() {
		stack <int> res;	//стек вершин в которых необходимо установить станции

		bool *isCovered = new bool[CountVertex];	//массив для отметок покрытых вершин
		memset(isCovered, false, CountVertex);

		//Копирование матрицы смежности
		int **matrix = new int*[CountVertex];

		for (int i = 0; i < CountVertex; i++) {
			matrix[i] = new int[CountVertex];
		}

		for (int i = 0; i < CountVertex; i++) {
			for (int j = 0; j < CountVertex; j++) {
				matrix[i][j] = adjMatrix[i][j];
			}
		}

		findCover(res, isCovered, matrix, findMaxDegreeVertex(matrix, isCovered));
	}

	// Рекурсивная функция для поиска вершинного покрытия
	void findCover(stack <int> res, bool *isCovered, int **matrix, int vertex) {
		// Если нет вершин со степенью > 0 
		if (vertex == INT_MAX) {
			// Устанавливаем станции в непокрытых вершинах
			for (int i = 0; i < CountVertex; i++) {
				if (!isCovered[i]) {
					isCovered[i] = true;
					res.push(i);
				}
			}

			// Вывод результата
			cout << "\nMilitary base cover =" << BaseRange;
			outFile << "Military base cover =" << BaseRange;

			cout << "\n The base must be located at following places:" << endl;
			outFile << "The base must be located at following places:" << endl;

			while (!res.empty()) {
				cout << res.top() << " ";
				outFile << res.top() << " ";
				res.pop();
			}

			cout << endl;

			// Выход из рекурсии
			return;
		}

		// Текущая вершина отмечается покрытой и добавлеятся в результат

		isCovered[vertex] = true;
		res.push(vertex);


		//Проход по ребрам инцидентным вершине
		for (int i = 0; i < CountVertex; i++) {
			// Если вес ребра меньше дальности передачи, удаляем его, инцидентные вершины отмечаем как покрытые
			if (matrix[vertex][i] != 0 && matrix[vertex][i] <= BaseRange) {
				matrix[i][vertex] = 0;
				matrix[vertex][i] = 0;
				isCovered[i] = true;
			}
		}

		// Переход в вершину с максимальной степенью
		findCover(res, isCovered, matrix, findMaxDegreeVertex(matrix, isCovered));
	}
};

int main() {

	//Проверка наличия файла с входными данными
	if (!inpFile.is_open()) {
		cout << "File doesn't exist\n";
		outFile << "File doesn't exist\n";

		inpFile.close();
		outFile.close();

		return 0;
	}

	inpFile.clear();
	inpFile.seekg(0, ios_base::beg);

	//Проверка на пустоту первой строки
	char str[100] = " ";
	inpFile.getline(str, 100);
	if (strcmp(str, "\0") == 0) {
		cout << "File is empty\n";
		outFile << "File is empty\n";

		inpFile.close();
		outFile.close();

		return 0;
	}

	inpFile.clear();
	inpFile.seekg(0, ios_base::beg);


	int size = 0;			//Количество вершин графа
	inpFile >> size;
	cout << size;
	Graph graph(size);

	int range = 0;
	inpFile >> range;
	cout << range;
	graph.setBaseRange(range);

	int strIndex = 0, columnIndex = 0, weight;		//Переменные для чтения из файла

	//Чтение из файла
	while (inpFile.peek() != '$') {

		inpFile >> weight;
		graph.addEdge(strIndex, columnIndex, weight);
		columnIndex++;
		if (inpFile.peek() == ',') {
			char ch;
			inpFile >> ch;

			if (inpFile.peek() == '\n') {
				strIndex++;
				columnIndex = 0;
			}
		}
	}
	//Печать матрицы смежности
	graph.printMatrix();

	//Поиск вершинного покрытия
	graph.findVertexCover();

	inpFile.close();
	outFile.close();

	return 0;
}

