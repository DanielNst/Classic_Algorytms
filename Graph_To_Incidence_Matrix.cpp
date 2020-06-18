// algoritmy_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace std;
class edges
{	
	public:
	int head, tail;
	edges(int new_head, int new_tail)
	{
		head = new_head;
		tail = new_tail;
	}
};

class graph
{
	public:
	const int N = 100;
	list<edges*>* Collection;
	int n;
	graph() {
		n = 0;
		Collection = new list<edges*>();
	}
	void Add(int head, int tail)
	{
		edges *tmp = new edges(head, tail);
		Collection->push_front(tmp);
		if (tail > n)
			n = tail;
		if (head > n)
			n = head;
	}
	void check() {
		if (n * (n + 1)  == Collection->size())
			makeMatrix();
		else
			cout << "Not full";
	}
private:
	void makeMatrix()
	{
		//vector<int>* matrix = new vector<int>();
		bool matrix[100][100];
		for (int i = 0; i < 100; i++) 
		{
			for (int j = 0; j < 100; j++)
			{
				matrix[i][j] = false;
			}
		}
		for (auto const& i : *Collection)
		{
			matrix[i->head][i->tail] = true;
		}
		for (int i = 0; i < n+1; i++)
		{
			for (int j = 0; j < n+1; j++)
			{
				if (matrix[i][j])
					cout << "1" << " ";
				else
					cout << "0" << " ";
			}
			cout<<endl;
		}
			
	}
};
int main()
{
	graph test;
	test.Add(0,1);
	test.Add(0,2);
	test.Add(0,3);
	test.Add(0,4);
	test.Add(1,0);
	test.Add(1,2);
	test.Add(1,3);
	test.Add(1,4);
	test.Add(2,1);
	test.Add(2,0);
	test.Add(2,3);
	test.Add(2,4);
	test.Add(3,0);
	test.Add(3,1);
	test.Add(3,2);
	test.Add(3,4);
	test.Add(4,0);
	test.Add(4,1);
	test.Add(4,2);
	test.Add(4,3);
	test.check();
}

