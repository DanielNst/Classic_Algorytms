#include "pch.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;
class edges
{
public:
	int head, tail,weight;
	edges(int new_head, int new_tail, int new_weight)
	{
		head = new_head;
		tail = new_tail;
		weight = new_weight;
	}
};

class graph
{
public:
	int matrix[100][100];
	list<edges*>* Collection;
	int n;
	graph() {
		n = 0;
		Collection = new list<edges*>();
	}
	void Add(int head, int tail, int weight)
	{
		edges *tmp = new edges(head, tail, weight);
		Collection->push_front(tmp);
		if (tail > n)
			n = tail;
		if (head > n)
			n = head;
	}
	void FromFile()
	{
		ifstream infile;
		infile.open("infile.txt"); //Проверка файла
		int current = 0;
		string check = " ";
		int counter = 0;
		do
		{
			infile >> check;
			counter++;
		} while (check != "$");
		infile.close();
		infile.open("infile.txt");
		cout << "Number of elements without spaces: " << counter-1 << endl;
		counter--;
		counter = sqrt(counter);
		for (int i = 0; i < counter; i++)
		{
			for (int j = 0; j < counter; j++)
			{
				infile >> matrix[i][j];
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		infile.close();
	}
private:
};
	
int main()
{
	ifstream infile;
	graph test;
	test.FromFile();
}

